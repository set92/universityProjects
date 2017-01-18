package com.tobalsa.convertercoins;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, getString(R.string.cambiando), Snackbar.LENGTH_LONG).setAction("Action", null).show();
                Intent intent = new Intent(MainActivity.this, ConversorActivity.class);
                startActivity(intent);
            }
        });
    }

    public void encriptar(View v){
        TextView tvResultado =(TextView)findViewById(R.id.tvResultado);
        EditText etEncriptar =(EditText)findViewById(R.id.sbCantidad);

        String text = etEncriptar.getText().toString();
        String aux = "";

        for (int i = 0; i < text.length(); i++) {
            char letra = text.charAt(i);
            if(letra >= 'a' && letra <= 'm') letra += 13;
            else if(letra >= 'A' && letra <= 'M') letra += 13;
            else if(letra >= 'n' && letra <= 'z') letra -= 13;
            else if(letra >= 'N' && letra <= 'Z') letra -= 13;
            aux += letra;
            System.out.println(aux);
        }
        tvResultado.setText(aux);
    }
}
