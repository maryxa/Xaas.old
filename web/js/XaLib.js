/* Alessandro Mariotti
 * 
 * alex@xallegro.com
 * 
 * @file XaLibJs.js
 * 
 */

var DefaultController="";
var DefaultMethod="POST";
var DefaultAsync="true";
var DefaultTarget="html";
var DefaultJsEval="no";
var	FlowCheck=true;
var DefaultWithAlert="no";

var AllRequiredFields="Please ensure that all required fields, those with an *(red asterisk), have been completed and formatted correctly!";

/*
 * @function XaCallAsync
 * Function to perform  async call
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @param {function} Callback function 
 *
 * @return {Callback function}
 * 
 */
function XaCallAsync (controller,url,type,cb) {

    if(controller==="") {controller = DefaultController;};

    if (url!=="") {
    
        url.replace("&amp;", "&");
        var url = controller + "?" + url;

        if (type==="xml") {
 
            url=url+"&ResType=xml";
        }

        var xmlhttp;

        if (window.XMLHttpRequest) {

            xmlhttp = new XMLHttpRequest();

        } else {

            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        
        xmlhttp.onreadystatechange = function () {

            if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {

                if (type==="" || type==="text") {
                    
                    cb(xmlhttp.responseText);

                } else if (type==="xml") {

                    //console.log(xmlhttp.responseXML);
                    cb(xmlhttp.responseXML);
                }

            } else if (xmlhttp.status === 500) {

                alert("error sending async call: "+url);
                cb(0);
            }

        };

        xmlhttp.open("POST", url, true);
        xmlhttp.send(null);

    } else {

        alert("url parameter is empty");
        cb(0);
    }
};

function XaCheckUrlReload(link) {

    if(location.href===link) {
        location.reload(true); 
        return false;
    }
};

/*XML MANIPULATION*/
function XaParseXml (XmlStr) {

    if (typeof window.DOMParser !== "undefined") {
        
        var parser = new DOMParser();
        var XmlDoc = parser.parseFromString (XmlStr, "text/xml");
        return XmlDoc;

    } else if (typeof window.ActiveXObject !== "undefined" && new window.ActiveXObject("Microsoft.XMLDOM")) {

        var XmlDoc = new window.ActiveXObject("Microsoft.XMLDOM");
        XmlDoc.async = "false";
        XmlDoc.loadXML(XmlStr);
        return XmlDoc;

    } else {
        //console.log("No XML parser found");
        throw new Error("No XML parser found");
    };

};

function XaXmlGetElementByXpath (XmlDoc,XPathExpr) {

    var Element= XmlDoc.evaluate(XPathExpr, XmlDoc, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;

    return Element;
};

function XaXmlGetElementValueByXpath (XmlDoc,XPathExpr) {

    var ElementValue= XmlDoc.evaluate(XPathExpr, XmlDoc, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue.textContent;

    return ElementValue;
};

function XaXmlCountElementByXpath (XmlDoc,XPathExpr) {
    
    var ElementNum = XmlDoc.evaluate( 'count('+XPathExpr+')', XmlDoc, null, XPathResult.ANY_TYPE, null ).numberValue;

    return ElementNum;
};

function XaXmlGetTagNameByXpath (XmlDoc,XPathExpr) {

    var TagName = new Array();

    var Element= XmlDoc.evaluate(XPathExpr, XmlDoc, null, XPathResult.FIRST_ORDERED_NODE_TYPE, null).singleNodeValue;
    var nodesSnapshot = XmlDoc.evaluate('*', Element, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null );

    for ( var i=0 ; i < nodesSnapshot.snapshotLength; i++ ) {
        TagName.push(nodesSnapshot.snapshotItem(i).nodeName);
        //console.log(nodesSnapshot.snapshotItem(i).nodeName );
    };

    return TagName;
};

/*HTML ELEMENTS MANIPULATION*/
function XaElSetHrefById(Id,Value,IsJs) {

    if (IsJs==="yes") {
        
        Value="javascript:"+Value;
    };

    var a = document.getElementById(Id);
    a.href = Value;
};

function XaElRemoveChildByParentId (ParentId,Child) {
    
    var Parent = document.getElementById(ParentId);
    var Child=Parent.getElementsByTagName("ul")[0];

    Parent.removeChild(Child);
};

/*STYLE MANIPULATION*/
function XaStyleSetCssClassById (Id,ClassName) {

    var d = document.getElementById(Id).className=ClassName;
};

function XaStyleAddCssClassById (Id,ClassName) {
    var d = document.getElementById(Id);
    d.className = d.className + " "+ClassName;
};

function XaStyleSetCssClassByIdArray (IdArray,ClassName) {

    for(var i = 0; i < IdArray.length; i++){

	document.getElementById(IdArray[i]).className = ClassName;
    };
};

function XaStyleCheckClass(Id,ClassName) {
    
    var element = document.getElementById(Id);
    var HasClass = element.classList.contains(ClassName);
    
    //HasHasClass is boolean
    return HasClass;
};

//Async:=true,false
//Loader:=0,1
//ResponseType:= StringText,StringHtml,StringHtmlToAppend
//
//EXAMPLE XaCallAction('','XaUserLogin','','POST',false,0,'','XaUserLoginFrm');

/*
 * @function XaCallAction
 * Function to call Web Actions
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @param {string} Target - The inner tag for Async Calls with returns
 * @param {string} Method - POST or GET
 * @param {string} Async - "false" or "true"
 * @param {string} Loader - "yes" or "no" (or 1,0)
 * @param {string} LoaderTarget - Element Id to display the Loader
 * @param {string} FormId - Form Id to serialize and send
 * @param {string} ResponseType - StringText, StringHtml, StringHtmlToAppend
 * @param {string} JsEval - "yes" or "no" - enable the JS evaluation
 * @param {string} WithAlert - "yes" or "no" - enable the alert
 * @param {string} Alert - Alert message or ""
 *
 * @returns {booblean} 
 * 
 */
function XaCallAction(controller,url,target,method,async,loader,LoaderTarget,FormId,ResponseType,JsEval,WithAlert,Alert){

    if(controller==="") {controller = DefaultController;};
    if(method==="") {method = DefaultMethod; };
    if(async==="") {async = DefaultAsync;};

    if(loader===1 || loader==="yes"){
        document.getElementById(LoaderTarget).innerHTML = ('<div class="loader"></div>');
    }

    if(JsEval===""){ JsEval = DefaultJsEval; }

	if(WithAlert===""){
		WithAlert = DefaultWithAlert;
	}

	if (url!=="") {

		url.replace("&amp;", "&");
		var url = controller + "?" + url;

		if (FormId!==""){
                    url= url + "&" +XaSerializeForm (FormId);
		}

		var xmlhttp;

		if (window.XMLHttpRequest) {
			xmlhttp = new XMLHttpRequest();
		} else {
			xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
		}

		xmlhttp.onreadystatechange = function () {

			if (target===""){

				target="html";
			}

			if (xmlhttp.readyState === 4 && xmlhttp.status === 200) {

				if (ResponseType==="StringText"){

					if(WithAlert==="yes" && Alert==="") {
						alert(xmlhttp.responseText);
					
					} else if(WithAlert==="yes" && Alert!=="") {

						alert(Alert);

					} else {
						document.getElementById(target).value = xmlhttp.responseText;
						
					}

				} else if (ResponseType==="StringHtml") {
					document.getElementById(target).innerHTML = xmlhttp.responseText;
					
					if (JsEval==="yes") {

						var scripts = document.getElementById(target).getElementsByTagName('script');

						for (var i=0;i<scripts.length;i++) {

							eval(scripts[i].innerHTML);
						}
					}

					if(WithAlert==="yes"){
						alert(Alert);
					}

				} else if (ResponseType==="StringHtmlToAppend") {

					var OldHtml = document.getElementById(target).innerHTML;
					document.getElementById(target).innerHTML = OldHtml + xmlhttp.responseText;

					if(WithAlert==="yes"){
						alert(Alert);
					}
				}

			} else if (xmlhttp.status === 500) {

				FlowCheck=false;
				alert("error sending async call: "+url);

			} else {

			}
		};

		if (FormId!==""){	
			var FormValidity=document.getElementById(FormId).checkValidity();
		}

		if(FormValidity===true || FormId===''){

			FlowCheck=true;
			xmlhttp.open(method, url, async);
			xmlhttp.send();

		} else {

			FlowCheck=false;
			alert(AllRequiredFields);
		}

	} else {
		FlowCheck=false;
		//alert("url parameter is empty");
	}
};

function XaSerializeForm (FormId) {

/*
	for (var i=0;i<FormElement.length;i++){
		
		alert(FormElement.elements[i].nodeName);
		alert(FormElement.elements[i].name);
		alert(FormElement.elements[i].type);
		alert(FormElement.elements[i].value);
	}		
*/		
var FormElement = document.getElementById(FormId);

        var i, j, q = [];

        for (i = FormElement.elements.length - 1; i >= 0; i = i - 1) {

                if (FormElement.elements[i].name === "") {
                        continue;
                }

                switch (FormElement.elements[i].nodeName) {

					case 'INPUT':
                        switch (FormElement.elements[i].type) {
                        case 'text':
                        case 'hidden':
                        case 'password':
						case 'email':
						case 'search':
						case 'number':
                        //case 'button':
                        //case 'reset':
                        //case 'submit':
                                q.push(FormElement.elements[i].name + "=" + encodeURIComponent(FormElement.elements[i].value));
                                break;
                        case 'checkbox':
                        case 'radio':
                                if (FormElement.elements[i].checked) {
                                        q.push(FormElement.elements[i].name + "=" + encodeURIComponent(FormElement.elements[i].value));
                                }                                               
                                break;
                        }
                        break;
                        
						case 'file':

						break; 

					case 'TEXTAREA':
                        q.push(FormElement.elements[i].name + "=" + encodeURIComponent(FormElement.elements[i].value));
                        break;
					case 'SELECT':
                        switch (FormElement.elements[i].type) {
							case 'select-one':
                                q.push(FormElement.elements[i].name + "=" + encodeURIComponent(FormElement.elements[i].value));
                                break;
							case 'select-multiple':
                                for (j = FormElement.elements[i].options.length - 1; j >= 0; j = j - 1) {
                                        if (FormElement.elements[i].options[j].selected) {
                                                q.push(FormElement.elements[i].name + "=" + encodeURIComponent(FormElement.elements[i].options[j].value));
                                        }
                                }
                                break;
                        }
                        break;
	/*
                case 'BUTTON':
                        switch (form.elements[i].type) {
                        case 'reset':
                        case 'submit':
                        case 'button':
                                q.push(form.elements[i].name + "=" + encodeURIComponent(form.elements[i].value));
                                break;
                        }
                        break;
											*/
                }
        }

    return q.join("&");
};