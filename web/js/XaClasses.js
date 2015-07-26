/* XAllegro Ltd 2013
 * 
 * www.xallegro.com - info@xallegro.com
 * 
 * @file XaClasses.js
 * 
 * Module to assign js behavior using class
 */

/* CLASSES:
 * JsWebAppLink: Replace href normal behavior with <windows.location> to work in a WebApp without open the external browser
 * 
 *  
 */


XaReady(function (){

/*
 *  @function WebAppLink
 *  Replace href normal behavior with <windows.location> to work in a WebApp without open the external browser
 * 
 */

function JsWebAppLink() {
	var a=document.getElementsByClassName("JsWebAppLink");

	for(var i=0 ;i<a.length ; i++) {

		a[i].onclick=function(){
			event.preventDefault();
			window.location=this.getAttribute("href");
			return false;
		};
	};

};


JsWebAppLink();

});