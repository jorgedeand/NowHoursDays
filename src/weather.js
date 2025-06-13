

function formatDay(day){
    var dia = 'Er';
    if(day.localeCompare('Mon') === 0){
      dia = 'Lu';
    }else if(day.localeCompare('Tue') === 0){
      dia = 'Ma';
    }else if(day.localeCompare('Wed') === 0){
      dia = 'Mi';
    }else if(day.localeCompare('Thu') === 0){
      dia = 'Ju';
    }else if(day.localeCompare('Fri') === 0){
      dia = 'Vi';
    }else if(day.localeCompare('Sat') === 0){
      dia = 'Sa';
    }else if(day.localeCompare('Sun') === 0){
      dia = 'Do';
    }
    return dia;
  }
  
  function formatDay2(day){
    var dia = 'Er';
    if(day.localeCompare('Mon') === 0){
      dia = 'Mo';
    }else if(day.localeCompare('Tue') === 0){
      dia = 'Tu';
    }else if(day.localeCompare('Wed') === 0){
      dia = 'We';
    }else if(day.localeCompare('Thu') === 0){
      dia = 'Th';
    }else if(day.localeCompare('Fri') === 0){
      dia = 'Fr';
    }else if(day.localeCompare('Sat') === 0){
      dia = 'Sa';
    }else if(day.localeCompare('Sun') === 0){
      dia = 'Su';
    }
    return dia;
  }

var getWeatherData = new XMLHttpRequest();
//getWeatherData.open('GET', 'http://api.wunderground.com/api/03e0e1f313bb096b/geolookup/astronomy/conditions/forecast10day/hourly10day/q/zmw:00000.4.08219.json', true);
getWeatherData.onload = function(e) {
  var json = JSON.parse(getWeatherData.responseText);
  //console.log(getWeatherData.responseText);
  
  //now******************************************************************
  //tempnow
  var temp_now = json.current_observation.temp_c;
  temp_now = Math.round(temp_now);
  var temp_s_now = temp_now + '\u00B0';
  
  //tempicon
  var tempicon_now = json.current_observation.icon;
  function geticono(variableicon){
    if((variableicon.localeCompare('clear')===0)||(variableicon.localeCompare('sunny')===0)){
      variableicon = 'cle';
    }else if(variableicon.localeCompare('cloudy')===0){
      variableicon = 'clo';
    }else if((variableicon.localeCompare('flurries')===0)||(variableicon.localeCompare('sleet')===0)||
            (variableicon.localeCompare('chanceflurries')===0)||(variableicon.localeCompare('chancesleet')===0)){
      variableicon = 'flu';
    }else if(variableicon.localeCompare('fog')===0){
      variableicon = 'fog';
    }else if(variableicon.localeCompare('hazy')===0){
      variableicon = 'hzy';
    }else if((variableicon.localeCompare('mostlycloudy')===0)||(variableicon.localeCompare('partlysunny')===0)){
      variableicon = 'mcl';
    }else if((variableicon.localeCompare('mostlysunny')===0)||(variableicon.localeCompare('partlycloudy')===0)){
      variableicon = 'msu';
    }else if((variableicon.localeCompare('rain')===0)||(variableicon.localeCompare('chancerain')===0)){
      variableicon = 'rai';
    }else if((variableicon.localeCompare('snow')===0)||(variableicon.localeCompare('chancesnow')===0)){
      variableicon = 'snw';
    }else if((variableicon.localeCompare('tstorms')===0)||(variableicon.localeCompare('chancestorms')===0)){
      variableicon = 'str';
    }
    return variableicon;
  }
  tempicon_now = geticono(tempicon_now);
  //temp maxmin
  var tempmax_now = json.forecast.simpleforecast.forecastday[0].high.celsius + '\u00B0';
  var tempmin_now = json.forecast.simpleforecast.forecastday[0].low.celsius + '\u00B0';
  //lluvia
  var lluvia_now = json.forecast.simpleforecast.forecastday[0].qpf_allday.mm + ' mm';
  //sens term
  var sterm_now = json.current_observation.feelslike_c + '\u00B0C';
  //viento
  var viento_now = Math.round(json.current_observation.wind_kph) + ' km/h';
  //vientoicon
  var vientoicon_now = json.current_observation.wind_dir;
  if((vientoicon_now.localeCompare('North')===0)||(vientoicon_now.localeCompare('NNE')===0)||(vientoicon_now.localeCompare('NNW')===0)){
    vientoicon_now = 'N';
  }else if((vientoicon_now.localeCompare('East')===0)||(vientoicon_now.localeCompare('ENE')===0)||(vientoicon_now.localeCompare('ESE')===0)){
    vientoicon_now = 'E';
  }else if((vientoicon_now.localeCompare('South')===0)||(vientoicon_now.localeCompare('SSE')===0)||(vientoicon_now.localeCompare('SSW')===0)){
    vientoicon_now = 'S';
  }else if((vientoicon_now.localeCompare('West')===0)||(vientoicon_now.localeCompare('WNW')===0)||(vientoicon_now.localeCompare('WSW')===0)){
    vientoicon_now = 'W';
  }else if(vientoicon_now.localeCompare('Variable') === 0){
    vientoicon_now = 'V';
  }
  //presion
  var presion_now = json.current_observation.pressure_mb + ' mb';
  //sunrise set
  var sunrise_now = json.sun_phase.sunrise.hour + ':' +  json.sun_phase.sunrise.minute;
  var sunset_now = json.sun_phase.sunset.hour + ':' +  json.sun_phase.sunset.minute;
  //moonrise set
  //var moonrise_now = json.moon_phase.moonrise.hour + ':' +  json.moon_phase.moonrise.minute;
  //var moonset_now = json.moon_phase.moonset.hour + ':' +  json.moon_phase.moonset.minute;
  //moonphase
  var moonphase_now = json.moon_phase.phaseofMoon;
  var moonphasetxt_now = json.moon_phase.phaseofMoon;
  
  /*if(moonphase_now.localeCompare('New Moon')===0){
    moonphase_now = 'NU';
  }else if(moonphase_now.localeCompare('Waxing Crescent')===0){
    moonphase_now = 'C1';
  }else if(moonphase_now.localeCompare('First Quarter')===0){
    moonphase_now = 'C2';
  }else if(moonphase_now.localeCompare('Waxing Gibbous')===0){
    moonphase_now = 'C3';
  }else if(moonphase_now.localeCompare('Full Moon')===0){
    moonphase_now = 'LL';
  }else if(moonphase_now.localeCompare('Waning Gibbous')===0){
    moonphase_now = 'D1';
  }else if(moonphase_now.localeCompare('Last Quarter')===0){
    moonphase_now = 'D2';
  }else if(moonphase_now.localeCompare('Waning Crescent')===0){
    moonphase_now = 'D3';
  }*/
  
  //console.log('luna:'+parseInt(json.moon_phase.percentIlluminated));
  var moonlight_now = parseInt(json.moon_phase.percentIlluminated);
  if(moonlight_now <= 6){
    //new moon
    //console.log('luna nueva');
    moonphase_now = 0;
  }else if(moonlight_now <= 19){
    if(moonphasetxt_now.localeCompare('Waxing Crescent')===0){
      //C1
      //console.log('luna C1');
      moonphase_now = 1;
    } else{
      //D1
      //console.log('luna D7');
      moonphase_now = 15;
    }
  }else if(moonlight_now <= 31){
    if(moonphasetxt_now.localeCompare('Waxing Crescent')===0){
      //C2
      //console.log('luna C2');
      moonphase_now = 2;
    } else{
      //D2
      //console.log('luna D6');
      moonphase_now = 14;
    }
  }else if(moonlight_now <= 44){
    if((moonphasetxt_now.localeCompare('Waxing Crescent')===0)||(moonphasetxt_now.localeCompare('First Quarter')===0)){
      //C3
      //console.log('luna C3');
      moonphase_now = 3;
    } else{
      //D3
      //console.log('luna D5');
      moonphase_now = 13;
    }
  }else if(moonlight_now <= 56){
    if((moonphasetxt_now.localeCompare('Waxing Crescent')===0)||(moonphasetxt_now.localeCompare('First Quarter')===0)||(moonphasetxt_now.localeCompare('Waxing Gibbous')===0)){
      //C4
      //console.log('luna C4');
      moonphase_now = 4;
    } else{
      //D4
      //console.log('luna D4');
      moonphase_now = 12;
    }
  }else if(moonlight_now <= 69){
    if((moonphasetxt_now.localeCompare('First Quarter')===0)||(moonphasetxt_now.localeCompare('Waxing Gibbous')===0)){
      //C5
      //console.log('luna C5');
      moonphase_now = 5;
    } else{
      //D5
      //console.log('luna D3');
      moonphase_now = 11;
    }
  }else if(moonlight_now <= 81){
    if(moonphasetxt_now.localeCompare('Waxing Gibbous')===0){
      //C6
      //console.log('luna C6');
      moonphase_now = 6;
    } else{
      //D6
      //console.log('luna D2');
      moonphase_now = 10;
    }
  }else if(moonlight_now <= 94){
    if(moonphasetxt_now.localeCompare('Waxing Gibbous')===0){
      //C7
      //console.log('luna C7');
      moonphase_now = 7;
    } else{
      //D7
      //console.log('luna D1');
      moonphase_now = 9;
    }
  }else{
    //full moon
    //console.log('luna llena');
    moonphase_now = 8;
  }
  //console.log('fase:'+moonphasetxt_now+' num:'+moonphase_now);
  
  
  
  
  //hours*************************************************************************************
  var cabecera1_hours = 'h1';
  var cabecera2_hours = 'h2';
  var cabecera3_hours = 'h3';
  var cabecera4_hours = 'h4';
  var icon1_hours = 'i1';
  var icon2_hours = 'i2';
  var icon3_hours = 'i3';
  var icon4_hours = 'i4';
  var temp1_s_hours = 'te';
  var temp2_s_hours = 'te';
  var temp3_s_hours = 'te';
  var temp4_s_hours = 'te';
  var lluvia1_s_hours = 'll';
  var lluvia2_s_hours = 'll';
  var lluvia3_s_hours = 'll';
  var lluvia4_s_hours = 'll';
  var viento1_hours = 'vi';
  var viento2_hours = 'vi';
  var viento3_hours = 'vi';
  var viento4_hours = 'vi';
  var vientoicon1_hours = 'ic';
  var vientoicon2_hours = 'ic';
  var vientoicon3_hours = 'ic';
  var vientoicon4_hours = 'ic';
  
  if(parseInt(json.hourly_forecast[0].FCTTIME.hour)%3 === 0){
    cabecera1_hours = json.hourly_forecast[0].FCTTIME.hour+':00';
    cabecera2_hours = json.hourly_forecast[3].FCTTIME.hour+':00';
    cabecera3_hours = json.hourly_forecast[6].FCTTIME.hour+':00';
    cabecera4_hours = json.hourly_forecast[9].FCTTIME.hour+':00';
    icon1_hours = json.hourly_forecast[0].icon;
    icon2_hours = json.hourly_forecast[3].icon;
    icon3_hours = json.hourly_forecast[6].icon;
    icon4_hours = json.hourly_forecast[9].icon;
    temp1_s_hours = json.hourly_forecast[0].temp.metric + '\u00B0';
    temp2_s_hours = json.hourly_forecast[3].temp.metric + '\u00B0';
    temp3_s_hours = json.hourly_forecast[6].temp.metric + '\u00B0';
    temp4_s_hours = json.hourly_forecast[9].temp.metric + '\u00B0';
    if(parseInt(json.hourly_forecast[0].qpf.metric) === 0){
      lluvia1_s_hours = '';
    }else{
      lluvia1_s_hours = json.hourly_forecast[0].qpf.metric +' mm';
    }
    if(parseInt(json.hourly_forecast[3].qpf.metric) === 0){
      lluvia2_s_hours = '';
    }else{
      lluvia2_s_hours = json.hourly_forecast[3].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[6].qpf.metric) === 0){
      lluvia3_s_hours = '';
    }else{
      lluvia3_s_hours = json.hourly_forecast[6].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[9].qpf.metric) === 0){
      lluvia4_s_hours = '';
    }else{
      lluvia4_s_hours = json.hourly_forecast[9].qpf.metric +' mm';
    } 
    viento1_hours = json.hourly_forecast[0].wspd.metric;
    viento2_hours = json.hourly_forecast[3].wspd.metric;
    viento3_hours = json.hourly_forecast[6].wspd.metric;
    viento4_hours = json.hourly_forecast[9].wspd.metric;
    vientoicon1_hours = json.hourly_forecast[0].wdir.dir;
    vientoicon2_hours = json.hourly_forecast[3].wdir.dir;
    vientoicon3_hours = json.hourly_forecast[6].wdir.dir;
    vientoicon4_hours = json.hourly_forecast[9].wdir.dir;
    
  }else if(parseInt(json.hourly_forecast[1].FCTTIME.hour)%3 === 0){
    cabecera1_hours = json.hourly_forecast[1].FCTTIME.hour+':00';
    cabecera2_hours = json.hourly_forecast[4].FCTTIME.hour+':00';
    cabecera3_hours = json.hourly_forecast[7].FCTTIME.hour+':00';
    cabecera4_hours = json.hourly_forecast[10].FCTTIME.hour+':00';
    icon1_hours = json.hourly_forecast[1].icon;
    icon2_hours = json.hourly_forecast[4].icon;
    icon3_hours = json.hourly_forecast[7].icon;
    icon4_hours = json.hourly_forecast[10].icon;
    temp1_s_hours = json.hourly_forecast[1].temp.metric + '\u00B0';
    temp2_s_hours = json.hourly_forecast[4].temp.metric + '\u00B0';
    temp3_s_hours = json.hourly_forecast[7].temp.metric + '\u00B0';
    temp4_s_hours = json.hourly_forecast[10].temp.metric + '\u00B0';
    if(parseInt(json.hourly_forecast[1].qpf.metric) === 0){
      lluvia1_s_hours = '';
    }else{
      lluvia1_s_hours = json.hourly_forecast[1].qpf.metric +' mm';
    }
    if(parseInt(json.hourly_forecast[4].qpf.metric) === 0){
      lluvia2_s_hours = '';
    }else{
      lluvia2_s_hours = json.hourly_forecast[4].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[7].qpf.metric) === 0){
      lluvia3_s_hours = '';
    }else{
      lluvia3_s_hours = json.hourly_forecast[7].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[10].qpf.metric) === 0){
      lluvia4_s_hours = '';
    }else{
      lluvia4_s_hours = json.hourly_forecast[10].qpf.metric +' mm';
    } 
    viento1_hours = json.hourly_forecast[1].wspd.metric;
    viento2_hours = json.hourly_forecast[4].wspd.metric;
    viento3_hours = json.hourly_forecast[7].wspd.metric;
    viento4_hours = json.hourly_forecast[10].wspd.metric;
    vientoicon1_hours = json.hourly_forecast[1].wdir.dir;
    vientoicon2_hours = json.hourly_forecast[4].wdir.dir;
    vientoicon3_hours = json.hourly_forecast[7].wdir.dir;
    vientoicon4_hours = json.hourly_forecast[10].wdir.dir;
  }else if(parseInt(json.hourly_forecast[2].FCTTIME.hour)%3 === 0){
    cabecera1_hours = json.hourly_forecast[2].FCTTIME.hour+':00';
    cabecera2_hours = json.hourly_forecast[5].FCTTIME.hour+':00';
    cabecera3_hours = json.hourly_forecast[8].FCTTIME.hour+':00';
    cabecera4_hours = json.hourly_forecast[11].FCTTIME.hour+':00';
    icon1_hours = json.hourly_forecast[2].icon;
    icon2_hours = json.hourly_forecast[5].icon;
    icon3_hours = json.hourly_forecast[8].icon;
    icon4_hours = json.hourly_forecast[11].icon;
    temp1_s_hours = json.hourly_forecast[2].temp.metric + '\u00B0';
    temp2_s_hours = json.hourly_forecast[5].temp.metric + '\u00B0';
    temp3_s_hours = json.hourly_forecast[8].temp.metric + '\u00B0';
    temp4_s_hours = json.hourly_forecast[11].temp.metric + '\u00B0';
    if(parseInt(json.hourly_forecast[2].qpf.metric) === 0){
      lluvia1_s_hours = '';
    }else{
      lluvia1_s_hours = json.hourly_forecast[2].qpf.metric +' mm';
    }
    if(parseInt(json.hourly_forecast[5].qpf.metric) === 0){
      lluvia2_s_hours = '';
    }else{
      lluvia2_s_hours = json.hourly_forecast[5].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[8].qpf.metric) === 0){
      lluvia3_s_hours = '';
    }else{
      lluvia3_s_hours = json.hourly_forecast[8].qpf.metric +' mm';
    } 
    if(parseInt(json.hourly_forecast[11].qpf.metric) === 0){
      lluvia4_s_hours = '';
    }else{
      lluvia4_s_hours = json.hourly_forecast[11].qpf.metric +' mm';
    } 
    viento1_hours = json.hourly_forecast[2].wspd.metric;
    viento2_hours = json.hourly_forecast[5].wspd.metric;
    viento3_hours = json.hourly_forecast[8].wspd.metric;
    viento4_hours = json.hourly_forecast[11].wspd.metric;
    vientoicon1_hours = json.hourly_forecast[2].wdir.dir;
    vientoicon2_hours = json.hourly_forecast[5].wdir.dir;
    vientoicon3_hours = json.hourly_forecast[8].wdir.dir;
    vientoicon4_hours = json.hourly_forecast[11].wdir.dir;
  }  
  icon1_hours = geticono(icon1_hours);
  icon2_hours = geticono(icon2_hours);
  icon3_hours = geticono(icon3_hours);
  icon4_hours = geticono(icon4_hours);
    
  
  
  
  //day*************************************************************************************
  var cabeceranum1_days = json.forecast.simpleforecast.forecastday[0].date.day;
  var cabeceratxt1_days = json.forecast.simpleforecast.forecastday[0].date.weekday_short;
  var cabeceranum2_days = json.forecast.simpleforecast.forecastday[1].date.day;
  var cabeceratxt2_days = json.forecast.simpleforecast.forecastday[1].date.weekday_short;
  var cabeceranum3_days = json.forecast.simpleforecast.forecastday[2].date.day;
  var cabeceratxt3_days = json.forecast.simpleforecast.forecastday[2].date.weekday_short;
  var cabeceranum4_days = json.forecast.simpleforecast.forecastday[3].date.day;
  var cabeceratxt4_days = json.forecast.simpleforecast.forecastday[3].date.weekday_short;
  
  //Cabecera
  
  
  var cabecera1_days = formatDay(cabeceratxt1_days) +' '+cabeceranum1_days;
  var cabecera2_days = formatDay(cabeceratxt2_days) +' '+cabeceranum2_days;
  var cabecera3_days = formatDay(cabeceratxt3_days) +' '+cabeceranum3_days;
  var cabecera4_days = formatDay(cabeceratxt4_days) +' '+cabeceranum4_days;
  
  //icono
  var icon1_days = json.forecast.simpleforecast.forecastday[0].icon;
  var icon2_days = json.forecast.simpleforecast.forecastday[1].icon;
  var icon3_days = json.forecast.simpleforecast.forecastday[2].icon;
  var icon4_days = json.forecast.simpleforecast.forecastday[3].icon;
  icon1_days = geticono(icon1_days);
  icon2_days = geticono(icon2_days);
  icon3_days = geticono(icon3_days);
  icon4_days = geticono(icon4_days);
  
  //tempmax
  var tempmax1_days = json.forecast.simpleforecast.forecastday[0].high.celsius +'\u00B0';
  var tempmax2_days = json.forecast.simpleforecast.forecastday[1].high.celsius+'\u00B0';
  var tempmax3_days = json.forecast.simpleforecast.forecastday[2].high.celsius+'\u00B0';
  var tempmax4_days = json.forecast.simpleforecast.forecastday[3].high.celsius+'\u00B0';
  
  //tempmin
  var tempmin1_days = json.forecast.simpleforecast.forecastday[0].low.celsius +'\u00B0';
  var tempmin2_days = json.forecast.simpleforecast.forecastday[1].low.celsius+'\u00B0';
  var tempmin3_days = json.forecast.simpleforecast.forecastday[2].low.celsius+'\u00B0';
  var tempmin4_days = json.forecast.simpleforecast.forecastday[3].low.celsius+'\u00B0';
  
  //lluvia
  var lluvia1_s_days = json.forecast.simpleforecast.forecastday[0].qpf_allday.mm;
  var lluvia2_s_days = json.forecast.simpleforecast.forecastday[1].qpf_allday.mm;
  var lluvia3_s_days = json.forecast.simpleforecast.forecastday[2].qpf_allday.mm;
  var lluvia4_s_days = json.forecast.simpleforecast.forecastday[3].qpf_allday.mm;
  if(lluvia1_s_days === 0){
    lluvia1_s_days = '';
  }else if(lluvia1_s_days <10){
    lluvia1_s_days = lluvia1_s_days+' mm';
  }else{
    lluvia1_s_days = lluvia1_s_days+'mm';
  }
  if(lluvia2_s_days === 0){
    lluvia2_s_days = '';
  }else if(lluvia2_s_days <10){
    lluvia2_s_days = lluvia2_s_days+' mm';
  }else{
    lluvia2_s_days = lluvia2_s_days+'mm';
  }
  if(lluvia3_s_days === 0){
    lluvia3_s_days = '';
  }else if(lluvia3_s_days <10){
    lluvia3_s_days = lluvia3_s_days+' mm';
  }else{
    lluvia3_s_days = lluvia3_s_days+'mm';
  }
  if(lluvia4_s_days === 0){
    lluvia4_s_days = '';
  }else if(lluvia4_s_days <10){
    lluvia4_s_days = lluvia4_s_days+' mm';
  }else{
    lluvia4_s_days = lluvia4_s_days+'mm';
  }
  
  
  //graph hours
  
  var temp1_hours = parseInt(json.hourly_forecast[0].temp.metric);
  var temp2_hours = parseInt(json.hourly_forecast[1].temp.metric);
  var temp3_hours = parseInt(json.hourly_forecast[2].temp.metric);
  var temp4_hours = parseInt(json.hourly_forecast[3].temp.metric);
  var temp5_hours = parseInt(json.hourly_forecast[4].temp.metric);
  var temp6_hours = parseInt(json.hourly_forecast[5].temp.metric);
  var temp7_hours = parseInt(json.hourly_forecast[6].temp.metric);
  var temp8_hours = parseInt(json.hourly_forecast[7].temp.metric);
  var temp9_hours = parseInt(json.hourly_forecast[8].temp.metric);
  var temp10_hours = parseInt(json.hourly_forecast[9].temp.metric);
  var temp11_hours = parseInt(json.hourly_forecast[10].temp.metric);
  var temp12_hours = parseInt(json.hourly_forecast[11].temp.metric);
  var temp13_hours = parseInt(json.hourly_forecast[12].temp.metric);
  var temp14_hours = parseInt(json.hourly_forecast[13].temp.metric);
  var temp15_hours = parseInt(json.hourly_forecast[14].temp.metric);
  var temp16_hours = parseInt(json.hourly_forecast[15].temp.metric);
  var temp17_hours = parseInt(json.hourly_forecast[16].temp.metric);
  var temp18_hours = parseInt(json.hourly_forecast[17].temp.metric);
  var temp19_hours = parseInt(json.hourly_forecast[18].temp.metric);
  var temp20_hours = parseInt(json.hourly_forecast[19].temp.metric);
  var temp21_hours = parseInt(json.hourly_forecast[20].temp.metric);
  //var temp22_hours = parseInt(json.hourly_forecast[21].temp.metric);
  //var temp23_hours = parseInt(json.hourly_forecast[22].temp.metric);
  
  var i;
  var max = -100;
  var min = 100;
  for(i = 0;i<23;i++){
    if(parseInt(json.hourly_forecast[i].temp.metric)>max){
      max = parseInt(json.hourly_forecast[i].temp.metric);
    }
    if(parseInt(json.hourly_forecast[i].temp.metric)<min){
      min = parseInt(json.hourly_forecast[i].temp.metric);
    }
  }
  var tempmax_s_hours = max.toString();
  var tempmin_s_hours = min.toString();
  var tempmax_hours = parseInt(max);
  var tempmin_hours = parseInt(min);
  
  //etiquetas en grafico
  var etiqueta1_hours = (json.hourly_forecast[0].FCTTIME.hour).toString();
  var etiqueta2_hours = (json.hourly_forecast[10].FCTTIME.hour).toString();
  var etiqueta3_hours = (json.hourly_forecast[20].FCTTIME.hour).toString();
 
  
  //graph days 
  var max1_days = parseInt(json.forecast.simpleforecast.forecastday[0].high.celsius);
  var max2_days = parseInt(json.forecast.simpleforecast.forecastday[1].high.celsius);
  var max3_days = parseInt(json.forecast.simpleforecast.forecastday[2].high.celsius);
  var max4_days = parseInt(json.forecast.simpleforecast.forecastday[3].high.celsius);
  var max5_days = parseInt(json.forecast.simpleforecast.forecastday[4].high.celsius);
  var max6_days = parseInt(json.forecast.simpleforecast.forecastday[5].high.celsius);
  var max7_days = parseInt(json.forecast.simpleforecast.forecastday[6].high.celsius);
  var max8_days = parseInt(json.forecast.simpleforecast.forecastday[7].high.celsius);
  var max9_days = parseInt(json.forecast.simpleforecast.forecastday[8].high.celsius);
  var max10_days = parseInt(json.forecast.simpleforecast.forecastday[9].high.celsius);
  var min1_days = parseInt(json.forecast.simpleforecast.forecastday[0].low.celsius);
  var min2_days = parseInt(json.forecast.simpleforecast.forecastday[1].low.celsius);
  var min3_days = parseInt(json.forecast.simpleforecast.forecastday[2].low.celsius);
  var min4_days = parseInt(json.forecast.simpleforecast.forecastday[3].low.celsius);
  var min5_days = parseInt(json.forecast.simpleforecast.forecastday[4].low.celsius);
  var min6_days = parseInt(json.forecast.simpleforecast.forecastday[5].low.celsius);
  var min7_days = parseInt(json.forecast.simpleforecast.forecastday[6].low.celsius);
  var min8_days = parseInt(json.forecast.simpleforecast.forecastday[7].low.celsius);
  var min9_days = parseInt(json.forecast.simpleforecast.forecastday[8].low.celsius);
  var min10_days = parseInt(json.forecast.simpleforecast.forecastday[9].low.celsius);
  
  max = -100;
  min = 100;
  for(i = 0;i<10;i++){
    if(parseInt(json.forecast.simpleforecast.forecastday[i].high.celsius)>max){
      max = parseInt(json.forecast.simpleforecast.forecastday[i].high.celsius);
    }
    if(parseInt(json.forecast.simpleforecast.forecastday[i].low.celsius)<min){
      min = parseInt(json.forecast.simpleforecast.forecastday[i].low.celsius);
    }
  }
  var tempmax_s_days = max.toString();
  var tempmin_s_days = min.toString();
  var tempmax_days = parseInt(max);
  var tempmin_days = parseInt(min);
  
  var etiqueta1_days = (json.forecast.simpleforecast.forecastday[0].date.day).toString();
  var etiqueta2_days = (json.forecast.simpleforecast.forecastday[7].date.day).toString();
  
  
  var moonrise_now = localStorage.getItem(13);
  var moonset_now = localStorage.getItem(14);
  
  //anadir hora de actualizacion
  var tiempo = new Date();
  localStorage.setItem(0,tiempo.getTime());
  
  Pebble.sendAppMessage({0: 0, 1: temp_s_now, 2: tempicon_now, 3: tempmax_now, 4: tempmin_now, 5: lluvia_now, 6: sterm_now, 7: viento_now, 8: vientoicon_now, 9: presion_now, 10: sunrise_now, 11: sunset_now, 12: moonphase_now, 
                         15: cabecera1_hours, 16: cabecera2_hours, 17: cabecera3_hours, 18: cabecera4_hours, 19: temp1_s_hours, 20: temp2_s_hours, 21: temp3_s_hours, 22: temp4_s_hours, 23: lluvia1_s_hours, 24: lluvia2_s_hours, 25: lluvia3_s_hours, 26: lluvia4_s_hours, 27: viento1_hours, 28: viento2_hours, 29: viento3_hours, 30: viento4_hours,
                         31: vientoicon1_hours, 32: vientoicon2_hours, 33: vientoicon3_hours, 34: vientoicon4_hours, 
                         35: cabecera1_days, 36: cabecera2_days, 37: cabecera3_days, 38: cabecera4_days, 39: tempmax1_days, 40: tempmax2_days, 41: tempmax3_days, 42: tempmax4_days, 43: tempmin1_days, 44: tempmin2_days, 45: tempmin3_days, 46: tempmin4_days, 47: lluvia1_s_days, 48: lluvia2_s_days, 49: lluvia3_s_days, 50: lluvia4_s_days,
                         51: icon1_hours, 52: icon2_hours, 53: icon3_hours, 54: icon4_hours, 55: icon1_days, 56: icon2_days, 57: icon3_days, 58: icon4_days, 
                         59: tempmax_s_hours, 60: tempmin_s_hours, 61: tempmax_hours, 62: tempmin_hours, 
                         63: temp1_hours, 64: temp2_hours, 65: temp3_hours, 66: temp4_hours, 
                         67: temp5_hours, 68: temp6_hours, 69: temp7_hours, 70: temp8_hours, 
                         71: temp9_hours, 72: temp10_hours, 73: temp11_hours, 74: temp12_hours, 
                         75: temp13_hours, 76: temp14_hours, 77: temp15_hours, 78: temp16_hours, 
                         79: temp17_hours, 80: temp18_hours, 81: temp19_hours, 82: temp20_hours, 83: temp21_hours,
                         84: max1_days, 85: max2_days, 86: max3_days, 87: max4_days, 
                         88: max5_days, 89: max6_days, 90: max7_days, 91: max8_days, 
                         92: max9_days, 93: max10_days, 
                         94: min1_days, 95: min2_days, 96: min3_days, 97: min4_days, 
                         98: min5_days, 99: min6_days, 100: min7_days, 101: min8_days, 
                         102: min9_days, 103: min10_days,
                         104: tempmax_days, 105: tempmin_days, 106: tempmax_s_days, 107: tempmin_s_days, 
                         108: etiqueta1_hours, 109: etiqueta2_hours, 110: etiqueta3_hours,
                         111: etiqueta1_days, 112: etiqueta2_days, 
                         13: moonrise_now, 14: moonset_now,
                        });
  
};









/*********** MOON **************/
function setLocalMoonData(datos){
  localStorage.setItem(13, datos[0]);
  localStorage.setItem(14, datos[1]);
}

var getMoonData = new XMLHttpRequest();
getMoonData.onload = function(e) {
  var json = JSON.parse(getMoonData.responseText);
  //console.log(getMoonData.responseText);
  var moonrise_now = json.data.weather[0].astronomy[0].moonrise;
  if(moonrise_now[0] == 'N'){
    moonrise_now = '--:--';
  }else{
    var horarise = parseInt(moonrise_now.substring(0,2));
    if(moonrise_now[6] == 'P'){
      if(horarise != 12){
        horarise = horarise +12;
      }
    }
    moonrise_now = horarise + moonrise_now.substring(2,5);
  }
  var moonset_now = json.data.weather[0].astronomy[0].moonset;
  if(moonset_now[0] == 'N'){
    moonset_now = '--:--';
  }else{
    var horaset = parseInt(moonset_now.substring(0,2));
    if(moonset_now[6] == 'P'){
      if(horaset != 12){
        horaset = horaset +12;
      }
    }
    moonset_now = horaset + moonset_now.substring(2,5);
  }
  var datos = [moonrise_now, moonset_now];
  setLocalMoonData(datos);
};



/*****************************************************/


var locationOptions = {
  enableHighAccuracy: true, 
  maximumAge: 10000, 
  timeout: 10000
};

function locationSuccess(pos) {
  var lat = (pos.coords.latitude).toFixed(2);
  var lon = (pos.coords.longitude).toFixed(2);
  //debug colmenar
  //lat = 40.67;
  //lon = -3.77;
  getMoonData.open('GET', 'http://api2.worldweatheronline.com/free/v2/weather.ashx?key=[API_KEY]&q='+lat+','+lon+'&format=json', true);
  getWeatherData.open('GET', 'http://api.wunderground.com/api/03e0e1f313bb096b/geolookup/astronomy/conditions/forecast10day/hourly10day/q/'+lat+','+lon+'.json', true);
  getMoonData.send(null);
  getWeatherData.send(null);
}

function locationError(err) {
  console.log('location error (' + err.code + '): ' + err.message);
  Pebble.sendAppMessage({0: 2,});
}


/*******************************************************/

// Called when JS is ready
Pebble.addEventListener("ready",
							function(e) {
                if(localStorage.getItem(0) === null){
                  //actualizar
                  navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
                }else{
                  var date_us = localStorage.getItem(0);
                  var date = new Date();
                  date.setTime(date_us);
                  var date2 = new Date();
                  if((parseInt(date2.getTime()/1000)-parseInt(date.getTime()/1000)) > 3600){
                    //actualizar, ha pasado mas de una hora desde la ultima vez
                    //console.log('mas de una hora, actualiza');
                    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
                  }else{
                    //ha pasado menos de una hora, ha cambiado de hora?
                    if(date2.getHours()!=date.getHours()){
                      //actualizar, las horas son distintas
                      navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
                      //console.log('menos de una hora,horas distintas: date:'+date.toString()+' date2:'+date2.toString());
                    }else{
                      //no actualizar, aun esta en la misma hora
                      //console.log('menos de una hora,horas iguales: date:'+date.toString()+' date2:'+date2.toString());
                      Pebble.sendAppMessage({0: 0,});
                    }
                  }
                }
							});


// Called when incoming message from the Pebble is received
Pebble.addEventListener("appmessage",
							function(e) {
                
                switch(e.payload.comando){
                  case 0:
                    //getWeatherData.send(null);
                    //getMoonData.send(null);
                    navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);   
                    break;
                }
							});