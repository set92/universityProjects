#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <list>
#include <map>
#include <set>
#include <vector>
#include "tools.h"
#include "trfm3D.h"
#include "scene.h"
#include "nodeManager.h"
#include "gObjectManager.h"
#include "shaderManager.h"
#include "lightManager.h"
#include "cameraManager.h"
#include "avatarManager.h"
#include "textureManager.h"
#include "json.h"

using std::string;
using std::list;
using std::map;
using std::set;
using std::vector;

static void ps_error(char *f, char *str) {

	fprintf(stderr, "[E] %s: %s\n", f, str);
	exit(1);

}

static bool json_string(Json::Value & o, string & res) {
	if (o.isNull()) return false;
	if (!o.isString()) return false;
	res = o.asString();
	return true;
}

static bool json_float(Json::Value & o, float &res) {
	if (o.isNull()) return false;
	if (!o.isDouble()) return false;
	res = o.asFloat();
	return true;
}

static bool json_int(Json::Value & o, int & res) {
	if (o.isNull()) return false;
	if (!o.isIntegral()) return false;
	res = o.asInt();
	return true;
}

static bool json_bool(Json::Value & o, bool & res) {
	if (o.isNull()) return false;
	if (!o.isBool()) return false;
	res = o.asBool();
	return true;
}

static bool json_vec(Json::Value & o, Vector3 &res) {
	if (o.isNull()) return false;
	if (!o.isArray()) return false;
	if (o.size() < 3)  return false;
	if (!o[0].isNumeric()) return false;
	if (!o[1].isNumeric()) return false;
	if (!o[2].isNumeric()) return false;
	res = Vector3(o[0].asFloat(), o[1].asFloat(), o[2].asFloat());
	return true;
}

//
// possible keys
//
// trans : [ x, y, z ]
// rotVec : { vec : [vx, vy, vz], angle : theta }
// rotAxis : { vec : [vx, vy, vz], point : [ px, py, pz], angle : theta }
// scale : { sc : factor }

static Trfm3D parse_trfm(Json::Value & jstrfm, const string & name) {

	Trfm3D res;
	if(!jstrfm["trans"].isNull()) {
		Vector3 T;
		if(!json_vec(jstrfm["trans"], T)) {
			fprintf(stderr, "[E] reading JSON file: invalid trans in node %s.\n", name.c_str());
			exit(1);
		}
		res.setTrans(T);
	}
	if(!jstrfm["rotVec"].isNull()) {
		Json::Value & jsrotVec = jstrfm["rotVec"];
		Vector3 V;
		float r;
		bool P = (json_vec(jsrotVec["vec"], V) &&
				  (json_float(jsrotVec["angle"], r) && r != 0.0f));
		if(!P) {
			fprintf(stderr, "[E] reading JSON file: invalid rotVec in node %s.\n", name.c_str());
			exit(1);
		}
		res.setRotVec(V, r);
	}
	if(!jstrfm["rotAxis"].isNull()) {
		Json::Value & jsrotAxis = jstrfm["rotAxis"];
		Vector3 V;
		Vector3 Point;
		float r;
		bool P = (json_vec(jsrotAxis["vec"], V) &&
				  json_vec(jsrotAxis["point"], Point) &&
				  (json_float(jsrotAxis["angle"], r) && r != 0.0f));
		if(!P) {
			fprintf(stderr, "[E] reading JSON file: invalid rotAxis in node %s.\n", name.c_str());
			exit(1);
		}
		res.setRotAxis(V, Point, r);
	}
	if(!jstrfm["scale"].isNull()) {
		Json::Value & jsScale = jstrfm["scale"];
		float sc;
		if (json_float(jsScale["factor"], sc) && sc > Constants::distance_epsilon)
			res.setScale(sc);
		else {
			fprintf(stderr, "[E] reading JSON file: invalid scale in node %s.\n", name.c_str());
			exit(1);
		}
	}
	return res;
}

static Trfm3D parse_trfms(Json::Value & jstrfm, const string & name) {
	if (!jstrfm.isArray()) {
		fprintf(stderr, "[E] reading JSON file: trfms has to be an array (node %s).\n", name.c_str());
		exit(1);
	}
	int n = jstrfm.size();
	Trfm3D T;
	for(int i = 0; i < n; i++) {
		Trfm3D t = parse_trfm(jstrfm[i], name);
		T.add(t);
	}
	return T;
}

static void populate_gObjs(Json::Value & gObjs) {
	// gObjs is of type json::type_t::array
	if(!gObjs.isArray()) {
		fprintf(stderr, "[E] reading JSON file: no gObjs.\n");
		exit(1);
	}
	int n = gObjs.size();
	for(int i = 0; i < n; i++) {
		Json::Value & gObj = gObjs[i];
		string fname, dirname;
		if (!json_string(gObj["fname"], fname)) {
			fprintf(stderr, "[E] reading JSON file: gObj with no fname.\n");
			exit(1);
		}
		if (!json_string(gObj["dirname"], dirname)) {
			fprintf(stderr, "[E] reading JSON file: gObj %s with no dirname.\n", fname.c_str());
			exit(1);
		}
		GObject * gobj = GObjectManager::instance()->createFromWavefront(dirname, fname);
		if(!gObj["trfm"].isNull()) {
			Trfm3D T = parse_trfms(gObj["trfm"], gobj->getName());
			gobj->applyTrfm(&T);
		}
	}
}

static void populate_shaders(Json::Value &shaders) {

	// shaders is of type json::type_t::array
	if(!shaders.isArray()) {
		fprintf(stderr, "[E] reading JSON file: no shaders.\n");
		exit(1);
	}
	int n = shaders.size();
	for(int i = 0; i < n; i++) {
		Json::Value & shader = shaders[i];
		string name, vname, fname;
		if (!json_string(shader["name"], name)) {
			fprintf(stderr, "[E] reading JSON file: shader with no name.\n");
			exit(1);
		}
		if (!json_string(shader["vshader"], vname)) {
			fprintf(stderr, "[E] reading JSON file: shader %s with no vshader.\n", vname.c_str());
			exit(1);
		}
		if (!json_string(shader["fshader"], fname)) {
			fprintf(stderr, "[E] reading JSON file: shader %s with no fshade.\n", fname.c_str());
			exit(1);
		}
		ShaderManager::instance()->create(name, vname, fname);
	}
}

static void populate_avatars(Json::Value & avatars) {
	// avatars is of type json::type_t::array
	if(!avatars.isArray()) {
		fprintf(stderr, "[E] reading JSON file: no avatars.\n");
		exit(1);
	}
	int n = avatars.size();
	for(int i = 0; i < n; i++) {
		Json::Value & avatar = avatars[i];
		string name, cameraName;
		if (!json_string(avatar["name"], name)) {
			fprintf(stderr, "[E] reading JSON file: avatar with no name.\n");
			exit(1);
		}
		if (!json_string(avatar["camera"], cameraName)) {
			fprintf(stderr, "[E] reading JSON file: avatar %s with no camera.\n", name.c_str());
			exit(1);
		}
		Camera *cam = CameraManager::instance()->find(cameraName);
		if (!cam) {
			fprintf(stderr, "[E] reading JSON file: avatar pointing to unkwnown camera %s.\n", cameraName.c_str());
			exit(1);
		}
		float radius;
		if(!json_float(avatar["radius"], radius)) radius = 1.0f;
		AvatarManager::instance()->create(name, cam, radius);
	}
}

static void populate_cameras(Json::Value & cameras) {

	// cameras is of type json::type_t::array
	if(!cameras.isArray()) {
		fprintf(stderr, "[E] reading JSON file: no cameras.\n");
		exit(1);
	}
	int n = cameras.size();
	for(int i = 0; i < n; i++) {
		Json::Value & camera = cameras[i];
		bool P;
		string name, type;
		Vector3 pos, at, up;
		if (!json_string(camera["name"], name)) {
			fprintf(stderr, "[E] reading JSON file: camera with no name.\n");
			exit(1);
		}
		if (!json_string(camera["type"], type)) {
			fprintf(stderr, "[E] reading JSON file: camera %s has no type.\n", name.c_str());
			exit(1);
		}
		P = (json_vec(camera["pos"], pos) &&
			 json_vec(camera["lookAt"], at) &&
			 json_vec(camera["up"], up));
		if (!P) {
			fprintf(stderr, "[E] reading JSON file: bad parameters for camera %s.\n", name.c_str());
			exit(1);
		}
		Camera *newCamera;
		if (type == "perspective") {
			float fovy, aspect, near, far;
			P = ((json_float(camera["fovy"], fovy) && fovy > 0.0f) &&
				 (json_float(camera["aspect"], aspect) && aspect > 0.0f) &&
				 (json_float(camera["near"], near) && near > 0.0f) &&
				 (json_float(camera["far"], far) && (far > near)));
			if (!P) {
				fprintf(stderr, "[E] reading JSON file: bad parameters for camera %s.\n", name.c_str());
				exit(1);
			}
			PerspectiveCamera *newCamera = CameraManager::instance()->createPerspective(name);
			newCamera->init(fovy, aspect, near, far);
			newCamera->lookAt(pos, at, up);
		} else if (type == "orthographic") {
			float left, right, top, bottom, near, far;
			P = ((json_float(camera["left"], left)) &&
				 (json_float(camera["right"], right) && right > left) &&
				 (json_float(camera["near"], near) && near > 0.0f) &&
				 (json_float(camera["far"], far) && (near > far)) &&
				 (json_float(camera["top"], top)) &&
				 (json_float(camera["bottom"], bottom) && (top > bottom)));
			if (!P) {
				fprintf(stderr, "[E] reading JSON file: bad parameters for camera %s.\n", name.c_str());
				exit(1);
			}
			OrthographicCamera *newCamera = CameraManager::instance()->createOrthographic(name);
			newCamera->init(left, right, bottom, top, near, far);
			newCamera->lookAt(pos, at, up);
		} else {
			fprintf(stderr, "[E] reading JSON file: camera %s has unknown type %s.\n", name.c_str(), type.c_str());
			exit(1);
		}
	}
}

static Light::type_t check_light_type(const string & type) {
	if (type == "positional") return Light::positional;
	if (type == "directional") return Light::directional;
	if (type == "spotlight") return Light::spotlight;
	return Light::invalid;
}

static void populate_lights(Json::Value & lights) {

	// lights is of type json::type_t::array
	if(!lights.isArray()) {
		fprintf(stderr, "[E] reading JSON file: no lights.\n");
		exit(1);
	}
	int n = lights.size();
	for(int i = 0; i < n; i++) {
		Json::Value & light = lights[i];
		bool P;
		string name, type;
		if (!json_string(light["name"], name)) {
			fprintf(stderr, "[E] reading JSON file: light with no name.\n");
			exit(1);
		}
		if (!json_string(light["type"], type)) {
			fprintf(stderr, "[E] reading JSON file: light %s has  type.\n", name.c_str());
			exit(1);
		}
		Light::type_t ltype = check_light_type(type);
		if (ltype == Light::invalid) {
			fprintf(stderr, "[E] reading JSON file: light %s has invalid type %s (possible values \"positional\", \"directional\", \"spotlight\")\n", name.c_str(), type.c_str());
			exit(1);
		}
		Vector3 pos, amb, dif, spec, att;
		float shin;
		P = (json_vec(light["pos"], pos) &&
			 json_vec(light["amb"], amb) &&
			 json_vec(light["dif"], dif) &&
			 json_vec(light["spec"], spec));
		if (!P) {
			fprintf(stderr, "[E] reading JSON file: bad or insufficient parameters for light %s.\n", name.c_str());
			exit(1);
		}
		Light *l = LightManager::instance()->create(name, ltype);
		l->setPosition(pos);
		l->setAmbient(amb);
		l->setDiffuse(dif);
		l->setSpecular(spec);

		if ((ltype != Light::directional) &&
			json_vec(light["attenuation"], att)) {
			l->setConstantAttenuation(att[0]);
			l->setLinearAttenuation(att[1]);
			l->setQuadraticAttenuation(att[2]);
		}
		if ( ltype == Light::spotlight ) {
			// check exp, cutoff, spdir
			Vector3 spdir;
			float exp, cutoff;
			P = ((json_float(light["exp"], exp) && exp > 0.0f) &&
				 (json_float(light["cutoff"], cutoff) && cutoff > 0.0f) &&
				 (json_vec(light["spdir"], spdir) && !spdir.isZero()));
			if (!P) {
				fprintf(stderr, "[E] reading JSON file: bad or insufficient parameters for spotlight %s.\n", name.c_str());
				exit(1);
			}
			l->setSpotData(spdir, cutoff, exp);
		}
		int switched;
		if (json_int(light["switched"], switched)) l->switchLight(switched != 0);
	}
}

static Texture::type_t check_texture_type(const string & type) {
	if (type == "tex") return Texture::tex;
	if (type == "rt_depth") return Texture::rt_depth;
	if (type == "rt_color") return Texture::rt_color;
	if (type == "cubemap") return Texture::cubemap;
	if (type == "bumpmap") return Texture::bumpmap;
	if (type == "proj") return Texture::proj;
	return Texture::empty;
}

static void populate_textures(Json::Value & textures) {

	if(textures.isNull()) return;
	// textures is of type json::type_t::array
	if(!textures.isArray()) {
		fprintf(stderr, "[E] reading JSON file: bad textures.\n");
		exit(1);
	}
	TextureManager *tm = TextureManager::instance();
	int n = textures.size();
	for(int i = 0; i < n; i++) {
		Json::Value & texture = textures[i];
		bool P;
		string name, type;
		if (!json_string(texture["name"], name)) {
			fprintf(stderr, "[E] reading JSON file: texture with no name.\n");
			exit(1);
		}
		Texture::type_t ttype;
		if (!json_string(texture["type"], type))
			ttype = Texture::tex;
		else
			ttype = check_texture_type(type);
		int height, width;
		string xpos, xneg, ypos, yneg, zpos, zneg;
		switch (ttype) {
		case Texture::empty:
			fprintf(stderr, "[E] reading JSON file: texture %s has invalid type %s (see texture.h for possible values)\n", name.c_str(), type.c_str());
			exit(1);
			break;
		case Texture::tex:
			tm->create(name);
			break;
		case Texture::bumpmap:
			tm->createBumpMap(name);
			break;
		case Texture::proj:
			tm->createProj(name);
			break;
		case Texture::rt_depth:
		case Texture::rt_color:
			if(!json_int(texture["height"], height)) {
				fprintf(stderr, "[E] reading JSON file: RT texture %s with no height.\n", name.c_str());
				exit(1);
			}
			if(!json_int(texture["width"], width)) {
				fprintf(stderr, "[E] reading JSON file: RT texture %s with no width.\n", name.c_str());
				exit(1);
			}
			if(ttype == Texture::rt_depth)
				tm->createDepthMap(name, height, width);
			else
				tm->createColorMap(name, height, width);
			break;
		case Texture::cubemap:
			if (!json_string(texture["xpos"], xpos)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'xpos'\n", name.c_str());
				exit(1);
			}
			if (!json_string(texture["xneg"], xneg)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'xneg'\n", name.c_str());
				exit(1);
			}
			if (!json_string(texture["ypos"], ypos)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'ypos'\n", name.c_str());
				exit(1);
			}
			if (!json_string(texture["yneg"], yneg)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'yneg'\n", name.c_str());
				exit(1);
			}
			if (!json_string(texture["zpos"], zpos)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'zpos'\n", name.c_str());
				exit(1);
			}
			if (!json_string(texture["zneg"], zneg)) {
				fprintf(stderr, "[E] reading JSON file: cubemap texture %s has no 'zneg'\n", name.c_str());
				exit(1);
			}
			tm->createCubeMap(name,
							  xpos, xneg,
							  ypos, yneg,
							  zpos, zneg);
			break;
		}
	}
}

static Node *populate_nodes(Json::Value &jsnode, Node *parent = 0) {

	// lights is of type json::type_t::array
	if(!jsnode.isObject()) {
		fprintf(stderr, "[E] reading JSON file: no node.\n");
		exit(1);
	}
	string name;
	if (!json_string(jsnode["name"], name)) {
		fprintf(stderr, "[E] reading JSON file: node with no name.\n");
		exit(1);
	}
	Node *node = NodeManager::instance()->create(name);
	if (!jsnode["trfm"].isNull()) {
		Trfm3D T = parse_trfms(jsnode["trfm"], name);
		node->addTrfm(&T);
	}
	string shaderName;
	if (json_string(jsnode["shader"], shaderName)) {
		ShaderProgram * shader = ShaderManager::instance()->find(shaderName);
		if (!shader) {
			fprintf(stderr, "[E] reading JSON file: node %s with invalid shader %s.\n", name.c_str(), shaderName.c_str());
			exit(1);
		}
		node->attachShader(shader);
	}

	string gObjName;
	bool has_gObj = false;
	if (json_string(jsnode["gObj"], gObjName)) {
		GObject * gObj = GObjectManager::instance()->find(gObjName);
		if (!gObj) {
			fprintf(stderr, "[E] reading JSON file: node %s with invalid gObj %s.\n", name.c_str(), gObjName.c_str());
			exit(1);
		}
		node->attachGobject(gObj);
		bool has_gObj = true;
	}
	if (!jsnode["children"].isNull()) {
		if (has_gObj) {
			fprintf(stderr, "[E] reading JSON file: node %s has gObject and children.\n", name.c_str());
			exit(1);
		}
		Json::Value & jschildren = jsnode["children"];
		int m = jschildren.size();
		for(int i = 0; i < m; i++)
			populate_nodes(jschildren[i], node);
	}
	if (parent) parent->addChild(node);
	return node;
}

static void populate_sky(Json::Value & jssky) {
	// jssky is null or of type json::type_t::object
	// sky : { gObj : "./obj/cubes/bigcube.obj",
	//         cubemap : "skyCubemap",
	//         shader : "sky"}
	if(jssky.isNull()) return;
	if(!jssky.isObject()) {
		fprintf(stderr, "[E] reading JSON file: sky must be an object.\n");
		exit(1);
	}
	// texture
	string cmap_name;
	if (!json_string(jssky["cubemap"], cmap_name)) {
		fprintf(stderr, "[E] reading JSON file: sky has no cubemap\n");
		exit(1);
	}
	Texture *cmap = TextureManager::instance()->find(cmap_name);
	if(!cmap || cmap->getType() != Texture::cubemap) {
		fprintf(stderr, "[E] reading JSON file: sky has invalid cubemap '%s'\n", cmap_name.c_str());
		exit(1);
	}
	// gObject
	string gObjName;
	if (!json_string(jssky["gObj"], gObjName)) {
		fprintf(stderr, "[E] reading JSON file: sky has no gObj\n");
		exit(1);
	}
	GObject *gObj = GObjectManager::instance()->find(gObjName);
	if (!gObj) {
		fprintf(stderr, "[E] reading JSON file: sky has with invalid gObj %s.\n", gObjName.c_str());
		exit(1);
	}
	gObj->setTexture(cmap);
	// shader
	string shaderName;
	if (!json_string(jssky["shader"], shaderName)) {
		fprintf(stderr, "[E] reading JSON file: sky has no shader\n");
		exit(1);
	}
	ShaderProgram * skyshader = ShaderManager::instance()->find(shaderName);
	if (!skyshader) {
		fprintf(stderr, "[E] reading JSON file: sky has invalid shader '%s'.\n", shaderName.c_str());
		exit(1);
	}
	// create node
	Node *skynode = NodeManager::instance()->create("MG_SKY");
	skynode->attachShader(skyshader);
	skynode->attachGobject(gObj);
}

static Node * populate_scene(Json::Value &scenejs) {

// avatars json::value_t::array
// cameras json::value_t::array
// gObjects json::value_t::array
// lights json::value_t::array
// shaders json::value_t::array
// node json::value_t::object

	Node *root;
	populate_cameras(scenejs["cameras"]);
	populate_avatars(scenejs["avatars"]);
	populate_gObjs(scenejs["gObjects"]);
	populate_shaders(scenejs["shaders"]);
	populate_lights(scenejs["lights"]);
	populate_textures(scenejs["textures"]);
	populate_sky(scenejs["sky"]);
	root = populate_nodes(scenejs["node"]);
	return root;
}

Node *parse_scene(const string &fname) {

	std::ifstream is;
	is.open(fname.c_str(), std::ifstream::in);
	if (!is) {
		printf("[E] Can't open %s\n", fname.c_str());
		exit(-1);
	}
	Json::Value scenejs;
	is >> scenejs;
	return populate_scene(scenejs);

}
