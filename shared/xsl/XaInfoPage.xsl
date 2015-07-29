<xsl:template match="//errors">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html id="html">

	<head>
		<xsl:call-template name="XaGuiHead"/>
    </head>

    <body id="body">

			<div class="container" style="left:0;top:0">
				<span class="ErrorMessage">
					<xsl:value-of select="//errors/*[name()=$ErrorMessage]/description"/>
				</span>
			</div>

    </body>

</html>
</xsl:template>