<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html>

	<head>
		<xsl:call-template name="XaGuiHead"/>
    </head>
	<!--head>
		<script>
			month_label = ['','<xsl:value-of select="/root/labels/label[@name='Jan']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Feb']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Mar']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Apr']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='May']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Jun']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Jul']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Aug']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Sep']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Oct']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Nov']/disp"/>', '<xsl:value-of select="/root/labels/label[@name='Dec']/disp"/>'];
			payment_for = '<xsl:value-of select="/root/labels/label[@name='PaymentFor']/disp"/>';
		</script>
		<script type="text/javascript" src="js/user_employee.js"></script>
		<script type="text/javascript" src="js/user_company.js"></script>
		<script type="text/javascript" src="js/user_department.js"></script>
		<script type="text/javascript" src="js/sort_table.js"></script>

		<title><xsl:value-of select="/root/labels/label[@name='XaUserOrgTreeView-title']/disp"/></title>
		<xsl:call-template name="head"/>
		
	</head-->

	<body id="body">

		<header>
			<xsl:call-template name="XaGuiHeader"/>
		</header>

		<nav>
			<xsl:call-template name="XaGuiNav"/>
		</nav>

	<div class="container">

		<div class="explorer">
			<div id="tree" class="tree">

				<script>XaCallAction('','obj=XaOu&amp;evt=Tree','tree','POST',true,1,'tree','','StringHtml');</script>

			</div>
			<div class="detail"></div>
		</div>
		
	</div>
		
		
		<!--div id="breadcrumb"><xsl:value-of select="/root/labels/label[@name='XaUserOrgTreeView-Breadcrumb']/disp"/-->	
			<!--xsl:value-of select="/root/labels/label[@name='MonthlySalaryPaidChanges']/disp"/-->
			
			<!--xsl:call-template name="input-checkbox">
				<xsl:with-param name="label-path" select="/root/labels/label[@name='']"/>
				<xsl:with-param name="path" select="/root/XaUserEmployeeList/fieldset/field[@id='monthly_salary_paid-Filter']"/>
			</xsl:call-template-->

			<!--input type="checkbox">
				<xsl:attribute name="id">LoginFilter</xsl:attribute>
				<xsl:attribute name="name">LoginFilter</xsl:attribute-->
				<!--xsl:if test="$checked='true'"><xsl:attribute name="checked">checked</xsl:attribute></xsl:if-->

				<!--xsl:attribute name="onchange">XaCallAction('','obj=XaUserEmployee&amp;evt=XaUserOrgTree&amp;LoginFilter='+document.getElementById('LoginFilter').checked,'aside','POST',true,1,'aside','','StringHtml');document.getElementById('detail').innerHTML = ''; </xsl:attribute>
			</input>

		</div>
		
		
		
	</div-->
	
	<!--xsl:call-template name="modal-window"/-->
	</body>

<!--script>XaCallAction('','obj=XaUserEmployee&amp;evt=XaUserOrgTree','aside','POST',true,1,'aside','','StringHtml');</script-->

</html>
</xsl:template>