<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html>
	<head>
		<xsl:call-template name="XaGuiHead"/>
	</head>

	<body id="body">
		<header id="header"><xsl:call-template name="XaGuiHeader"/></header>
		<nav id="nav"><xsl:call-template name="XaGuiNav"/></nav>

			<div class="container">

			<table class="list">
				<tr class="title">
					<td colspan="100%"><span>Lista canali</span>

						<ul class="RightToolbar">
							<li class="FunctionIcon Refresh"></li>
							<li class="FunctionIcon Expand"></li>
						</ul>
					</td>
				</tr>
				<tr class="header">
					<th>Id</th>
					<th>Name</th>
					<th>Description</th>
				</tr>

				<xsl:for-each select="//OuTypes/OuType">

					<tr class="row">
						<td><xsl:value-of select="./id"/></td>
						<td><xsl:value-of select="./name"/></td>
						<td><xsl:value-of select="./description"/></td>
					</tr>

				</xsl:for-each>

			</table>
		</div>
	</body>

</html>
</xsl:template>