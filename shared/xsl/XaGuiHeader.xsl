<xsl:template name="XaGuiHeader">
	<!--ol id="toolbar">
		<li id="menu" onclick="XaToggleMenu();"></li>
	

		<li id="settings">
			<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserPasswordModFrm"><img src="img/IconSettings.svg" alt="settings" title="settings" height="55%" width="55%" style="padding-top: 0.4em;"/></a>
		</li>
	</ol-->

	<ul class="LeftToolbar">

		<li class="MenuIcon MenuToggle"></li>
		<li class="MenuIcon MenuMyPage" onclick='XaCheckUrlReload(this.href)' href="?obj=XaPages&amp;evt=XaMyPage#MenuXaMyPage"></li>

	</ul>

	<ul class="CenterToolbar">
		<li>Admin</li>
		<li>Risorse Umane</li>
		<li>Utenti</li>
	</ul>
	
	<ul class="RightToolbar">
		
		<li class="MenuIcon MenuSettings"></li>
		<li class="MenuIcon MenuHelp"></li>

	</ul>
</xsl:template>