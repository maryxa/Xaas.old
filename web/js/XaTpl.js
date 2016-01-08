function XaFormTpl (ModelName) {

    var XmlDoc=XaParseXml(ModelName);

    var RootElement=XmlDoc.documentElement.nodeName;

    var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//fieldset/field");

    var Controller=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/controller");    
    var Id=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/id");
    var Name=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/name");
    var Obj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/obj");
    var Evt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/evt");
    var Async=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/async");
    var Method=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/method");
    var Class=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/form/class");
    var EncType="multipart/form-data";

    function BuildAction(){

        var Action="javascript:XaCallAction('','obj="+Obj+"&amp;evt="+Evt+"','','"+Method+"',"+Async+",0,'','"+Id+"','StringText','','yes','');";
        return Action;
    };

    function BuildField (FieldId) {

        var Field="";

        var FId=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/id");

        //var FId=Fields[RootElement]['fieldset']['field'][FieldId]["id"];
        var FName=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/name");
        var FType=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/type");
        var FLabel=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/label");
        var FPlaceholder=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/placeholder");

        var FDefault=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/default");

        var FRequired=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/required");
        
        if (FRequired==="yes") {
            FRequired=" required=\"required\" ";
        } else {
            FRequired="";
        };

        var FRead=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/read");
        var FUpdate=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/update");
        var FSearch=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/search");
        var FSize=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/size");

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

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");

            Field+="<script>XaCreateOptions('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"');</script>";

        } else if (FType==="select-single-ou-tree") {

            Field+="<label id=\""+ LId +"\" for=\""+FieldExtId +"\">"+FLabel+"</label>";
            Field+="<select id=\""+FieldExtId+ "\" name=\""+FieldExtName+"\" type=\""+FType+"\" placeholder=\""+FPlaceholder+"\"" + FRequired+" autofocus=\"autofocus\" ></select>";

            var FObj=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/obj");
            var FEvt=XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/field["+FieldId+"]/options/evt");

            Field+="<script>XaCreateOptionsOu('','obj="+FObj+"&evt="+FEvt+"','"+FieldExtId+"');</script>";

        } else {
            
        }

    return Field;
    };

    /*can access _privateProperty and call _privateMethod*/
    this.GetForm = function () {

        var Content="<form class=\"form "+Class+"\" id=\""+Id+"\""+ " name=\""+Name+"\" enctype=\""+EncType+ "\" method=\""+Method+"\""+ " action=\""+BuildAction()+ "\">";

        Content+="<fieldset>";
        Content+="<legend>"+ XaXmlGetElementValueByXpath (XmlDoc,"/"+RootElement+"/fieldset/legend")+"</legend>";
        Content+="<ul>";


        for(var i=0;i<FieldsNumber;i++) {
            var j=i+1;
            Content+="<li>"+BuildField(j)+"</li>";
        };

        Content+="</ul>";
        Content+="</fieldset>";
        Content+="<fieldset><button type=\"reset\">Reset</button><button type=\"submit\">Save</button></fieldset>";
        Content+="</form>";

        /*console.log(Content);*/
        //console.log(Fields);
        return Content;
    };
};

/*LIST*/
function XaListTpl (ModelName) {

    var XmlDoc=XaParseXml(ModelName);

    var RootElement=XmlDoc.documentElement.nodeName;
    var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//list/item");

    var TagsNames=Array();

    var ElementsNumbers;

    if (FieldsNumber>0) {

        ElementsNumbers=XaXmlCountElementByXpath(XmlDoc,"//list/item[0]");
    }

    function BuildHeader() {

        var ListHeader="<tr class=\"header\">";
        TagsNames=XaXmlGetTagNameByXpath(XmlDoc,"//item[1]");

        for(key in TagsNames) {
            ListHeader+="<th>"+TagsNames[key]+"</th>";
        }

        ListHeader+="</tr>";
        return ListHeader;
    };

    function BuildRow (FieldId) {

        var ListRow="<tr class=\"row\">";
        
        for(key in TagsNames) {

            var TagValue=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+FieldId+"]/"+TagsNames[key]);
            ListRow+="<td>"+TagValue+"</td>"; 
        }

    return ListRow;
    };

    this.GetList = function () {

        var Content="<table class=\"list\">";
        var Title="Titolo Lista";
 
        Content+="<tr class=\"title\"><td colspan=\"100%\"><span>"+Title+"</span><ul class=\"RightToolbar\"><li class=\"FunctionIcon Refresh\"></li><li class=\"FunctionIcon Expand\"></li></ul></td></tr>";

        Content+=BuildHeader();

        for(var i=0;i<FieldsNumber;i++) {

            Content+=BuildRow(i+1);
        };
        Content+="</table>";

        return Content;
    };
};

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
            
    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {

            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            Select.options[Select.options.length] = new Option(name,id);
        }
    });
};

/*
 * @function XaCreateOptionsWithOnChangeFunction
 * Function to Read Options From the Back End and Add them into a Select and with a CallBack function called Onchange 
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 * @param {string} function name - the callback function called Onchange
 * @returns {booblean} 
 *
 */
function XaCreateOptionsWithOnChangeFunction(controller,url,SelectId,OnChangeFunction){

    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {
            
            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            Select.options[Select.options.length] = new Option(name,id);
        }

        //ADDING CB FUNCTION
        Select.setAttribute("onchange", OnChangeFunction);
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

    XaCallAsync(controller,url,"xml", function(XmlDoc){

        var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");
        var Select=document.getElementById(SelectId);

        Select.options[Select.options.length] = new Option('... Select an option ...',"");

        for (var i=1;i<FieldsNumber+1;i++) {

            var indent="";

            var tree_level=parseInt(XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/tree_level"))+1;
            var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
            var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");

            for (var j=1;j<tree_level;j++) {
                indent=indent+"--";

                if (j===tree_level-1) {

                    indent=indent+">";
                }
            }

            Select.options[Select.options.length] = new Option(indent+name,id);
        }
    });
};

/*
 * @function XaTreeReadBranch specialized for OU
 * Function to Read a Branch of OU
 *
 * @param {string} Controller - The controller to use to build the url if is other than the default 
 * @param {string} Url - The URL to append to the Controller with pairs <param> and <value> the final construct will be: <Controller?param1=value1&param2=value2...>
 *
 * @returns {booblean} 
 * 
 */
function XaTreeBranchRead(controller,url,TargetId) {

    if (TargetId!=="" && XaStyleCheckClass("a-"+TargetId,"open")) {
            XaTreeBranchClose(TargetId);
 
    } else {
        
        if (TargetId!=="") {

            XaStyleSetCssClassById("a-"+TargetId,"open");

        };
    
        XaCallAsync(controller,url,"xml", function(XmlDoc){

            var FieldsNumber=XaXmlCountElementByXpath(XmlDoc,"//item");

            var Elements="<ul>";

            for (var i=1;i<FieldsNumber+1;i++) {

                var tree_level=parseInt(XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/tree_level"))+1;
                var name=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/name");
                var id=XaXmlGetElementValueByXpath (XmlDoc,"/WsData/list/item["+i+"]/id");
                var url="obj=XaOuUi&evt=Tree&tree_parent_ID="+id+"&tree_level="+tree_level;
                //var BranchCall='XaTreeBranchRead("","'+url+'","'+id+'");XaStyleSetCssClassById("a-'+id+'","open");XaElSetHrefById("a-'+id+'","XaTreeBranchClose('+id+')","yes");';
                var BranchCall='XaTreeBranchRead("","'+url+'","'+id+'");';

                var Element='<li id="'+id+'">'+

                    /*OPEN BRANCH*/
                    '<a id="a-'+id+ '" class="close" href=\'javascript:'+BranchCall+';\'></a>'+

                    /*LIST ELEMENT BRANCH*/
                    '<a class="name" href="javascript:alert(\'pluto\');">'+name+'</a>'+

                    /*READ THE OU WITH EDIT*/
                    '<a class="edit" href="javascript:alert(\'pippo\');"></a>'+
                    '</li>';

                Elements+=Element;

            }

            Elements+="</ul>";

            /*FIRST LEVEL*/
            if (TargetId==="") {
                TargetId="Tree";
            }

            var OldHtml = document.getElementById(TargetId).innerHTML;
            document.getElementById(TargetId).innerHTML = OldHtml + Elements;
        });
    
    }
};

function XaTreeBranchClose(Id) {

    XaStyleSetCssClassById("a-"+Id,"close");
    XaElRemoveChildByParentId (Id,"ul");
};