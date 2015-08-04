/* Alessandro Mariotti
 * 
 * alex@xallegro.com
 * 
 * @file XaUtil.js
 * 
 */

function XaSleep(MilliSeconds) {

    var start;
    var i;

    start = new Date().getTime();

    for (i = 0; i < 1e7; i++) {
		if ((new Date().getTime() - start) > MilliSeconds){
			break;
		}
	}
}



function XaSizeByteToHr (bytes) {

	var UnitMeasure= ['Bytes', 'KB', 'MB'];

	if (bytes === 0) {

		return 0;

	} else {

		var i = parseInt(Math.floor(Math.log(bytes) / Math.log(1024)));
		return (bytes / Math.pow(1024, i)).toFixed(1) + ' ' + UnitMeasure[i];

	}
}

/*
 * @function XaGetTimezone
 * Function To Get client Timezone
 */
function XaGetTimezone() {
    var offset = new Date().getTimezoneOffset();
    var minutes = Math.abs(offset);
    var hours = Math.floor(minutes / 60);
    var prefix = offset < 0 ? "+" : "-";
    return prefix+hours;
}

function XaFieldSetEnableStatus (ArrayFieldId,status) {


	for(var i = 0; i < ArrayFieldId.length; i++){

		var Field = document.getElementById(ArrayFieldId[i]);

		if (status===0){

			Field.setAttribute('disabled', 'disabled');

		} else if(status===1){

			Field.removeAttribute('disabled');

		}
	}
}

function XaFieldSetVisibilityStatus (ArrayFieldId,status) {

	for(var i = 0; i < ArrayFieldId.length; i++){

		var Field = document.getElementById(ArrayFieldId[i]);

		if (status===0){

			Field.hidden=true;
			Field.style.visibility="hidden";
			Field.style.display="none";

		} else if(status===1){

			Field.hidden=false;
			Field.style.visibility="visible";
			Field.style.display="inline-block";

		}
	}
}

function XaFieldSetRequired(ArrayFieldId,status) {

	for(var i = 0; i < ArrayFieldId.length; i++) {

		var Field = document.getElementById(ArrayFieldId[i]);

				if(status===1){

					Field.setAttribute("required",true);
	
				} else if(status===0){

					Field.removeAttribute("required");
				}
		}
}

function XaFormReset(FormId){

	if(FlowCheck){
		var FormElement = document.getElementById(FormId);	
		FormElement.reset();
	}
}

function XaAddCssFile(CssFile) {	

	var NewCssLink = document.createElement("link");
		NewCssLink.type = 'text/css';
		NewCssLink.rel = 'stylesheet';
		NewCssLink.href = CssFile;

	document.getElementsByTagName("head").item(0).appendChild(NewCssLink);
}

function XaChangeCssFile(CssFile, OldCssLinkPosition) {

	var OldCssLink = document.getElementsByTagName("link").item(OldCssLinkPosition);

	var NewCssLink = document.createElement("link");

		NewCssLink.setAttribute("rel", "stylesheet");
		NewCssLink.setAttribute("type", "text/css");
		NewCssLink.setAttribute("href", CssFile);

	document.getElementsByTagName("head").item(0).replaceChild(NewCssLink, OldCssLink);
}

function XaFieldApplyClassStyle (ArrayFieldId,ClassStyle) {

	for(var i = 0; i < ArrayFieldId.length; i++){

		document.getElementById(ArrayFieldId[i]).className = ClassStyle;

	}
}

function XaClassStyleAddFieldById (FieldId,ClassStyle) {
		
		var d = document.getElementById(FieldId);
		d.className = d.className + " "+ClassStyle;
}

function XaClassStyleSetFieldById (FieldId,ClassStyle) {
		
		var d = document.getElementById(FieldId).className=ClassStyle;
}

function XaFieldSetCssPropertyByName(FieldName,CssPropertyValue) {


	var e=document.getElementsByTagName(FieldName)[0];
	e.setAttribute("style",CssPropertyValue);
}

function XaFieldSetCssPropertyById(FieldId,CssPropertyValue) {

	if(FlowCheck){
		var e=document.getElementById(FieldId);

		if (e) {
			e.setAttribute("style",CssPropertyValue);
		}
	}
}

function XaFieldGetCssPropertyByName(FieldName,CssPropertyName) {

	var e=document.getElementsByTagName(FieldName)[0];
	var CssPropertyValue = document.defaultView.getComputedStyle(e,null).getPropertyValue(CssPropertyName);

return CssPropertyValue;
}

function XaFieldSetCssPropertyModal(FieldId,CssPropertyValue) {
		var e=document.getElementById(FieldId);

		if (e) {
			e.setAttribute("style",CssPropertyValue);
		}
}

function XaToggleMenu() {

	if (XaFieldGetCssPropertyByName("nav","visibility")==="visible") {
		
		XaFieldSetVisibilityStatus (['nav'],0);
		var WidthNavPercentage=parseFloat(XaFieldGetCssPropertyByName("nav","width"),10);

		var w = window;
		var x = parseFloat(w.innerWidth,10);
		var WidthNavPixel=x/100*WidthNavPercentage;
		var NewSectionWidth=parseFloat(XaFieldGetCssPropertyByName("section","width"),10)+WidthNavPixel+5;
		var CssProperty="width:"+NewSectionWidth+"px";

		XaFieldSetCssPropertyByName("section",CssProperty);
		XaFieldSetCssPropertyById("breadcrumb",CssProperty);


	} else {

		var WidthNavPercentage=parseFloat(XaFieldGetCssPropertyByName("nav","width"),10);

		var w = window;
		var x = parseFloat(w.innerWidth,10);
		var WidthNavPixel=x/100*WidthNavPercentage;

		var NewSectionWidth=parseFloat(XaFieldGetCssPropertyByName("section","width"),10)-WidthNavPixel-5;
		var CssProperty="width:"+NewSectionWidth+"px";

		NewSectionWidthBreadCrumb=NewSectionWidth-19;
		var CssPropertyBreadCrumb="width:"+NewSectionWidthBreadCrumb+"px";



		XaFieldSetCssPropertyByName("section",CssProperty);	
		XaFieldSetCssPropertyById("breadcrumb",CssPropertyBreadCrumb);	

		XaFieldSetVisibilityStatus (['nav'],1);
	}
}

function XaSetFocus(FieldId) {
	document.getElementById(FieldId).focus(); 
}