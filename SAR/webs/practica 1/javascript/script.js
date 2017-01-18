var quotes = [
	{ 
		"quote" : "The only sin is ignorance", 
	},
	{
		"quote" : "A man is his own easiest dupe, for what he wishes to be true he generally believes to be true", 
	},
	{
		"quote" : "When I get a little money I buy books; and if any is left I buy food and clothes", 
	},
	{
		"quote" : "Quote 1", 
	},
	{
		"quote" : "Quote 2", 
	},
	{
		"quote" : "Quote 3", 
	},
	{
		"quote" : "Quote 4", 
	}
]

function randomQuote() {
  let random = quotes[Math.floor(Math.random() * quotes.length)];
  quotation.innerText = `${random.quote}.`;
}

randomQuote();

document.querySelector("button").addEventListener("click", function() { randomQuote(); });
