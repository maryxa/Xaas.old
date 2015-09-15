<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html id="html">
	<head>
		<title>Dashboard</title>
		<xsl:call-template name="XaGuiHead"/>
	</head>

<body>
	<header><xsl:call-template name="XaGuiHeader"/></header>
	<nav><xsl:call-template name="XaGuiNav"/></nav>

	<div class="container"></div>

	<!--body onresize="drawChart1();drawChart2();drawChart3();">
		<header id="header"><xsl:call-template name="header"/></header>
		<nav id="nav"><xsl:call-template name="nav"/></nav>
		<div id="breadcrumb"><xsl:value-of select="/root/labels/label[@name='XaMyPage-Title']/disp"/>

		
			&#160;&#160;&#160;&#160;
			<xsl:value-of select="/root/labels/label[@name='XaUserSalaryForecastList-FromDate']/disp"/>:&#160;

			<xsl:call-template name="input-date">
				<xsl:with-param name="label-path" select="/root/labels/label[@name='']"/>
				<xsl:with-param name="path" select="/root/MlsClickChart/fieldset/field[@id='from']"/>
			</xsl:call-template>&#160;&#160;&#160;&#160;
	
			<xsl:value-of select="/root/labels/label[@name='XaUserSalaryForecastList-ToDate']/disp"/>:&#160;
			
			<xsl:call-template name="input-date">
				<xsl:with-param name="label-path" select="/root/labels/label[@name='']"/>
				<xsl:with-param name="path" select="/root/MlsClickChart/fieldset/field[@id='to']"/>
			</xsl:call-template>&#160;&#160;&#160;&#160;
		
			<button type="button">
				<xsl:attribute name="onclick">javascript:XaCallAction('','obj=XaPages&amp;evt=XaMyPage&amp;from_year='+document.getElementById('from_year').value+'&amp;to_year='+document.getElementById('to_year').value+'&amp;from_month='+document.getElementById('from_month').value+'&amp;to_month='+document.getElementById('to_month').value+'&amp;from_day='+document.getElementById('from_day').value+'&amp;to_day='+document.getElementById('to_day').value,'','POST',false,0,'html','','StringHtml','yes');</xsl:attribute>
				<xsl:value-of select="/root/labels/label[@name='ApplyFilter']/disp"/>
			</button>

		</div>

		
		<section id="XaMyPage" class="MyPage">
			<article>
				pluto				
			</article>
		</section>

		<footer id="footer">
			<xsl:call-template name="footer"/>
		</footer>

		<xsl:call-template name="modal-window"/-->

	</body>

</html>
</xsl:template>