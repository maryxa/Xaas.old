function XaFormTpl (ModelName) {

    var xml = ParseXml(ModelName);

    //PRIVATE
    var RootElement=xml.documentElement.nodeName;
    var Fields=xml2array(xml);
    var FieldsNumber=Object.keys(Fields[RootElement]['fieldset']['field']).length;

    var Controller=Fields[RootElement]['form']['controller'];
    var Id=Fields[RootElement]['form']['id'];
    var Name=Fields[RootElement]['form']['name'];
    var Obj=Fields[RootElement]['form']['obj'];
    var Evt=Fields[RootElement]['form']['evt'];
    var Async=Fields[RootElement]['form']['async'];
    var Method=Fields[RootElement]['form']['method'];
    var Class=Fields[RootElement]['form']['class'];
    var EncType="multipart/form-data";

    function BuildAction(){
    
        /*function XaCallAction(controller,url,target,method,async,loader,LoaderTarget,FormId,ResponseType,JsEval,WithAlert,Alert){*/

        var Action="javascript:XaCallAction('','obj="+Obj+"&amp;evt="+Evt+"','','"+Method+"',"+Async+",0,'','"+Id+"','StringText','','yes','');";
        return Action;
    };

    function BuildField (FieldId) {

        var Field="";

        var FId=Fields[RootElement]['fieldset']['field'][FieldId]["id"];
        var FName=Fields[RootElement]['fieldset']['field'][FieldId]["name"];
        var FType=Fields[RootElement]['fieldset']['field'][FieldId]["type"];
        var FLabel=Fields[RootElement]['fieldset']['field'][FieldId]["label"];
        var FOptions=Fields[RootElement]['fieldset']['field'][FieldId]["options"];
        var FPlaceholder=Fields[RootElement]['fieldset']['field'][FieldId]["placeholder"];

        var FDefault=Fields[RootElement]['fieldset']['field'][FieldId]["default"];

        var FRequired=Fields[RootElement]['fieldset']['field'][FieldId]["required"];
        
        if (FRequired==="yes") {
            FRequired=" required=\"required\" ";
        } else {
            FRequired="";
        };

        var FRead=Fields[RootElement]['fieldset']['field'][FieldId]["read"];
        var FUpdate=Fields[RootElement]['fieldset']['field'][FieldId]["update"];
        var FSearch=Fields[RootElement]['fieldset']['field'][FieldId]["search"];
        var FSize=Fields[RootElement]['fieldset']['field'][FieldId]["size"];

        var FieldExtId=RootElement+"-"+FId;
        var FieldExtName=RootElement+"-"+FName;

        var LId=FieldId+"-label";
        var LName=FieldExtName+"-label";

        if (FType==="input-text") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<input id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></input>";

        } else if (FType==="input-textarea") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<textarea id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></textarea>";

        } else if (FType==="select-single") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></select>";

            var FObj=Fields[RootElement]['fieldset']['field'][FieldId]['options']['obj'];
            var FEvt=Fields[RootElement]['fieldset']['field'][FieldId]['options']['evt'];

            Field+="<script>XaCreateOptions('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"');</script>";

        } else if (FType==="select-single-ou-tree") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></select>";

            var FObj=Fields[RootElement]['fieldset']['field'][FieldId]['options']['obj'];
            var FEvt=Fields[RootElement]['fieldset']['field'][FieldId]['options']['evt'];

            Field+="<script>XaCreateOptionsOu('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"');</script>";

        } else {
            
        }

    return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetForm = function () {

        var Content="<form class=\"form "+Class+"\" id=\""+Id+"\""+ " name=\""+Name+"\" enctype=\""+EncType+ "\" method=\""+Method+"\""+ " action=\""+BuildAction()+ "\">";

        Content+="<fieldset>";
        Content+="<legend>"+Fields[RootElement]['fieldset']['legend']+"</legend>";
        Content+="<ul>";

        for(var i=0;i<FieldsNumber;i++) {

            Content+="<li>"+BuildField(i)+"</li>";
        };

        Content+="</ul>";
        Content+="</fieldset>";
        Content+="<fieldset><button type=\"reset\">Reset</button><button type=\"submit\">Save</button></fieldset>";
        Content+="</form>";

        /*console.log(Content);*/
        console.log(Fields);
        return Content;
    };
};

/*LIST*/
function XaListTpl (ModelName) {

    var xml = ParseXml(ModelName);

    //PRIVATE
    var RootElement=xml.documentElement.nodeName;
    var Fields=xml2array(xml);
    var FieldsNumber=Object.keys(Fields[RootElement]['list']['item']).length;
    var ElementsNumbers;

    if (FieldsNumber>0) {
        /*Number of element for each item*/
        ElementsNumbers=Object.keys(Fields[RootElement]['list']['item'][0]).length;
    }

    function BuildHeader() { 
    
        var ListHeader="<tr class=\"header\">";

        for(var key in Fields[RootElement]['list']['item'][0]) {

            ListHeader+="<th>"+key+"</th>";
        }

        ListHeader+="</tr>";

        return ListHeader;
    };

    function BuildRow (FieldId) {

        var ListRow="<tr class=\"row\">";
        
        for(var key in Fields[RootElement]['list']['item'][FieldId]) { 

           ListRow+="<td>"+Fields[RootElement]['list']['item'][FieldId][key]+"</td>";
        }

    return ListRow;
    };

    /*can access _privateProperty and call _privateMethod*/

    this.GetList = function () {

        //BuildHeader();
        
        var Content="<table class=\"list\">";
       
        var Title="Titolo Lista";
 
        Content+="<tr class=\"title\"><td colspan=\"100%\"><span>"+Title+"</span><ul class=\"RightToolbar\"><li class=\"FunctionIcon Refresh\"></li><li class=\"FunctionIcon Expand\"></li></ul></td></tr>";
        
        

        Content+=BuildHeader();
        
        for(var i=0;i<FieldsNumber;i++) {

            Content+=BuildRow(i);
        };        
        Content+="</table>";

        return Content;
    };
};
/*
    this.publicProperty = 1;

    var _privateProperty = 2;
    function _privateMethod () {

         only private methods and privileged methods can call this
    };
*/

/*
 * @function XaCreateOptions
 * Function to Read Options From the Back End and Add them into a Select 
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaCreateOptions(controller,url,SelectId){
            
    XaCallAsync(controller,url, function(responseText){

        var xml = ParseXml(responseText);

        var RootElement=xml.documentElement.nodeName;
        var Fields=xml2array(xml);
        var FieldsNumber=Object.keys(Fields[RootElement]['list']['item']).length;

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=0;i<FieldsNumber;i++) {

            Select.options[Select.options.length] = new Option(Fields[RootElement]['list']['item'][i]['name'],Fields[RootElement]['list']['item'][i]['id']);
        }
    });
};
/*
 * @function XaCreateOptions specialized for OU
 * Function to Read Options OU From the Back End and Add them into a Select with indentation
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaCreateOptionsOu(controller,url,SelectId){

    XaCallAsync(controller,url, function(responseText){

        var xml = ParseXml(responseText);

        var RootElement=xml.documentElement.nodeName;
        var Fields=xml2array(xml);

        var FieldsNumber=Object.keys(Fields[RootElement]['list']['item']).length;

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=0;i<FieldsNumber;i++) {

            var indent="";

            var levels=Fields[RootElement]['list']['item'][i]['tree_level'];

            for (var j=1;j<levels;j++) {
                indent=indent+"--";

                if (j===levels-1) {

                    indent=indent+">";
                }
            }

            Select.options[Select.options.length] = new Option(indent+Fields[RootElement]['list']['item'][i]['name'],Fields[RootElement]['list']['item'][i]['id']);
        }
    });
};