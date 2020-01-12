const requestUrl = "https://api.breezometer.com/air-quality/v2/current-conditions?lat=-33.865143&lon=151.209900&key=571317b67bcd4b7588ba97663ff74a28&features=breezometer_aqi"

const xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
       // when the document is ready:
       cbFunction(xhttp.responseText);
    }
};
xhttp.open("GET", requestUrl, true);
xhttp.send();

// using a nested callback, instead of a promise
function cbFunction(data) {
    const things = JSON.parse(data);
    const aqi = things.data.indexes.baqi.aqi_display;
    const aqiDescript = things.data.indexes.baqi.category;
    const datetime = things.data.datetime;

    document.getElementById("aqi").innerHTML = aqi;
    document.getElementById("aqiDescript").innerHTML = aqiDescript;
    document.getElementById("datetime").innerHTML = datetime;
};
