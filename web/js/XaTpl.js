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

        var FieldId=RootElement+"-"+FId;
        var FieldName=RootElement+"-"+FName;

        var LId=FieldId+"-label";
        var LName=FieldName+"-label";

        Field+="<label id=\""+ LId +"\" for=\""+FieldId +"\">"+FLabel+"</label>";
        Field+="<input id=\""+FieldId+ "\" name=\""+FieldName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" />";

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


/*
    this.publicProperty = 1;

    var _privateProperty = 2;
    function _privateMethod () {

         only private methods and privileged methods can call this
    };
*/