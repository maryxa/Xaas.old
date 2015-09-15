<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html>
	<head>
		<link rel="stylesheet" type="text/css" href="/{$GuiStyle}/tree.css"/>
		<!--title><xsl:value-of select="/root/labels/label[@name='XaUserOrgTreeView-title']/disp"/></title-->
	</head>
				<!--form id="EmployeeQuickSearchFrm" name="EmployeeQuickSearchFrm" method="POST">
					<input style="margin:0.5em; width:40%;" id="mysearch2" name="mysearch2" type="search" placeholder="{/root/labels/label[@name='Menu-Organization-EmployeeQuickSearch']/disp}"/>
					<input id="EmployeeQuickSearchFrmButton" type="submit" onclick="XaCallAction('','obj=XaUserEmployee&amp;evt=XaUserEmployeeSearch','detail','POST',false,0,'','EmployeeQuickSearchFrm','StringHtml');">Search<xsl:value-of select="/root/labels/label[@name='Form-Search']/disp"/></input>
				</form-->
	<xsl:if test="$TplType='tree'">

		<!--aside-->
			<ol class="tree">
				<xsl:for-each select="/root/XaUserOrgTree/*">
					<xsl:if test="name()='ou'">
						<xsl:call-template name="tree-ou">

							<xsl:with-param name="path" select="."/>
							<xsl:with-param name="action-ou" select="'x'"/><!-- viene definita nella template -->
							<xsl:with-param name="action-user" select="'XaUserEmployeeView'"/>

						</xsl:call-template>
					</xsl:if>

					<xsl:if test="name()='user'">
						<xsl:call-template name="tree-user">

							<xsl:with-param name="path" select="."/>
							<xsl:with-param name="action-ou" select="'XaUserCompanyView'"/>
							<xsl:with-param name="action-user" select="'XaUserEmployeeView'"/>

						</xsl:call-template>
					</xsl:if>

				</xsl:for-each>
			</ol>
		<!--/aside-->
	</xsl:if>

	<xsl:if test="$TplType='chart'">

		<!--aside-->
			<ol class="tree">
				<xsl:for-each select="/root/XaUserOrgTree/*">
					<xsl:if test="name()='ou'">

						<xsl:call-template name="tree-ou">
							<xsl:with-param name="path" select="."/>
							<xsl:with-param name="action-ou" select="'XaUserOrgChart'"/>
						</xsl:call-template>

					</xsl:if>
					<!--xsl:if test="name()='user'">

						<xsl:call-template name="tree-user">
							<xsl:with-param name="path" select="."/>
						</xsl:call-template>

					</xsl:if-->
				</xsl:for-each>
			</ol>
		<!--/aside-->
	</xsl:if>
	
</html>
</xsl:template>