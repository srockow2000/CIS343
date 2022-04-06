let url = 'https://dog.ceo/api/breeds/image/random';

function getDoggo() {
	let response = await fetch(url);
	let json = await resonse.json();
	let doggo = document.getElementById('doggo');
	doggo.innerHTML = "<img src='" + json.message + "' />;
}
