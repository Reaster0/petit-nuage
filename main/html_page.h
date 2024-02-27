const char *index_html = "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Petit Nuage</title>\
</head>\
<body>\
	<h1 class=\"topScreen title\">Petit Nuage</h1>\
	<h1 class=\"connected\" style=\"display: none;\">Connected</h1>\
	<h1 class=\"disconnect\" style=\"display: none;\">Disconnected</h1>\
	<button class=\"btn rain\" id=\"rain-btn\">\
        <span>🌧️</span>\
    </button>\
	<div class=\"bottom\">made with ❤️ by Reaster</div>\
	\
</body>\
\
<script>\
	const btnRain = document.querySelector('#rain-btn');\
	\
	/* every half seconds, check if the server is connected by fetching the server and set the right class visible, if the fetch didn't succeded in 1s, the server is disconnected */\
	async function healthCheck() {\
		setInterval(() => {\
			try {\
				fetch('http://192.168.1.1/health')\
				.then(response => {\
					document.querySelector('.connected').style.display = 'block';\
					document.querySelector('.disconnect').style.display = 'none';\
				})\
				.catch(error => {\
					document.querySelector('.connected').style.display = 'none';\
					document.querySelector('.disconnect').style.display = 'block';\
				});\
			} catch (error) {\
				document.querySelector('.connected').style.display = 'none';\
				document.querySelector('.disconnect').style.display = 'block';\
			}\
		}, 500);\
	}\
\
	async function syncButtons() {\
		btnRain.classList.toggle('active');\
		fetch('http://192.168.1.1/status')\
			.then(response => response.json())\
			.then(data => {\
				console.log(data);\
				if (data.rain == false){\
					btnRain.classList.remove('active');\
				}\
				else{\
					btnRain.classList.add('active');\
				}\
			});\
	}\
	\
	btnRain.addEventListener('click', async () => {\
		await fetch('http://192.168.1.1/toggle/rain');\
		syncButtons();\
	});\
\
	syncButtons();\
	healthCheck();\
\
\
</script>\
\
<style lang=\"scss\">\
	body {\
		margin: 0; /* Remove default margin */\
		font-family: 'Arial', sans-serif;\
		text-align: center;\
		height: 100vh; /* Make the background cover the entire viewport height */\
		background: linear-gradient(to bottom, #00214A, #EA25B5);\
		display: flex;\
		flex-direction: column;\
		justify-content: center;\
		align-items: center;\
	}\
	\
	h1 {\
		color: white;\
		\
		text-transform: uppercase;\
		font-family: 'Montserrat';\
		font-weight: 200;\
		z-index: 2;\
	}\
\
	.topScreen {\
		position: absolute;\
		top: 20px;\
	}\
\
	.title {\
  font-size: 3em;\
  background: linear-gradient(to right, #0D3F7C, #EA25B5);\
  background-clip: text;\
  color: transparent;\
  font-family: 'Arial', sans-serif;\
  text-align: center;\
  margin: 0;\
  padding: 20px;\
}\
\
.btn {\
	width: 160px;\
	height: 160px;\
	cursor: pointer;\
	background: transparent;\
	border: 1px solid #ffffff;\
	outline: none;\
	transition: 1s ease-in-out;\
	margin: 20px;\
	border-radius: 50%; /* Make the button round */\
}\
\
.btn.active {\
	transition: 1s ease-in-out;\
  	background: #FF82F4;\
}\
\
.rain {\
	border: 1px solid #91C9FF;\
}\
\
.rain.active {\
  transition: 1s ease-in-out;\
  background: #04BBEC;\
}\
\
.btn.active svg {\
  stroke-dashoffset: -480;\
}\
\
.btn span {\
  color: white;\
  font-size: 50px;\
  font-weight: 100;\
}\
\
.bottom {\
  position: absolute;\
  bottom: 20px;\
  background: linear-gradient(to right, #0D3F7C, #FF82F4);\
  background-clip: text;\
  color: transparent;\
  font-family: 'Arial', sans-serif;\
}\
\
.connected{\
  position: relative;\
  color: #03A062;\
  font-weight: 700;\
  font-size: 20px;\
  padding-bottom: 40%;\
  letter-spacing: 5px;\
  text-transform: uppercase;\
}\
\
.disconnect{\
  position: relative;\
  color: #FF0000;\
  font-weight: 700;\
  font-size: 20px;\
  padding-bottom: 40%;\
  letter-spacing: 5px;\
  text-transform: uppercase;\
}\
\
</style>\
</html>\
";
