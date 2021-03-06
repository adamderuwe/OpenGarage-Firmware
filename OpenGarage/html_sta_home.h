const char html_sta_home[] PROGMEM = R"(<body>
<div data-role='page' id='page_home'>
<div data-role='header'><h3 id='head_name'>OG</h3></div>
<div data-role='content'>
<div data-role='fieldcontain'>
<table cellpadding='4'>
<tr><td><b>Distance:</b></td><td><label id='lbl_dist'>-</label></td></tr>
<tr><td><b>Door State:</b></td><td><label id='lbl_status'>-</label></td></tr>
<tr><td><b>Read Count:</b></td><td><label id='lbl_beat'>-</label></td></tr>
<tr><td><b>WiFi Signal:</b></td><td><label id='lbl_rssi'>-</label></td></tr>
<tr><td><b>Device Key:</b></td><td><input type='password' size=16 maxlength=32 name='dkey' id='dkey'></td></tr>
<tr><td colspan=2><label id='msg'></label></td></tr>
</table>
<br />
<div data-role='controlgroup' data-type='horizontal'>
<button data-theme='b' id='btn_click'>Button</button>  
<button data-theme='b' id='btn_opts'>Options</button>
<button data-theme='b' id='btn_log'>Show Log</button>
</div>
<span style='display:block;height:5px'></span>
<div data-role='controlgroup' data-type='horizontal'>
<button data-theme='c' id='btn_rap'>Reset to AP Mode</button>
<button data-theme='c' id='btn_rbt'>Reboot</button>
</div>
</div>
</div>
<div data-role='footer' data-theme='c'>
<p>&nbsp; OpenGarage Firmware <label id='fwv'>-</label>&nbsp;<a href='update' target='_top' data-role='button' data-inline=true data-mini=true>Update</a></p>
</div>
</div>
<script>
var si;
function clear_msg() {$('#msg').text('');}
function show_msg(s,t,c) {
$('#msg').text(s).css('color',c);
if(t>0) setTimeout(clear_msg, t);
}
$('#btn_opts').click(function(e){window.open('vo', '_top');});
$('#btn_log').click(function(e){window.open('vl', '_top');});
$('#btn_rbt').click(function(e){
if(confirm('Reboot the device now?')){
var comm = 'cc?reboot=1&dkey='+($('#dkey').val());
clear_msg();
$.getJSON(comm, function(jd) {
if(jd.result!=1) show_msg('Check device key and try again.',2000,'red');
else {
show_msg('Rebooting. Please wait...',0,'green');
clearInterval(si);
setTimeout(function(){location.reload(true);}, 10000);
}
});
}
});   
$('#btn_rap').click(function(e){
if(confirm('Reset the device to AP mode?')){
var comm = 'cc?apmode=1&dkey='+($('#dkey').val());
clear_msg();
$.getJSON(comm, function(jd) {
if(jd.result!=1) show_msg('Check device key and try again.',2000,'red');
else {
clearInterval(si);
$('#msg').html('Device is now in AP mode. Log on<br>to SSID OG_xxxxxx, then open a<br>browser, type in <a href="http://192.168.4.1">http://192.168.4.1</a><br>and continue there.').css('color','green');
}
});
}
});  
$('#btn_click').click(function(e) {
var comm = 'cc?click=1&dkey='+($('#dkey').val());
clear_msg();
$.getJSON(comm, function(jd) {
if(jd.result!=1) {
show_msg('Check device key and try again.',2000,'red');
}
});
});
$(document).ready(function() {
show(); si=setInterval('show()', 3000);
});
function show() {
$.getJSON('jc', function(jd) {
$('#fwv').text('v'+(jd.fwv/100>>0)+'.'+(jd.fwv/10%10>>0)+'.'+(jd.fwv%10>>0));
$('#lbl_dist').text(''+jd.dist+' (cm)');
$('#lbl_status').text(jd.door?'OPEN':'closed').css('color', jd.door?'red':'black');
$('#lbl_beat').text(jd.rcnt);
$('#lbl_rssi').text(jd.rssi+' dBm ('+(jd.rssi<-75?'weak':'ok')+')');
$('#head_name').text(jd.name);
});
}
</script>
</body>)";
