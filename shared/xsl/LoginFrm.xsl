<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html id="html">

    <head>
        <xsl:call-template name="XaGuiHead"/>
    </head>

    <body id="body">
		<!--header id="header"><xsl:call-template name="XaGuiHeaderInternet"/></header-->
		
        <div class="container" style="left:0;top:0">
            <form style="height:99%" class="form form-1-column" id="Login" name="Login" method="POST" action="?obj=XaUserLoginUi&amp;evt=Login">

                <fieldset>
                    <legend class="LogHomePage" style="line-height:2em" ><img height="50vh" src="/{$GuiStyle}/XAllegroLogo.svg" /></legend>

                    <ul>
                        <li>
                            <label id="username-label" for="username-input">Email</label>
                            <input id="username-input" name="username" type="email" placeholder="Please insert your Email" required="required" autofocus="autofocus" />
                        </li>

                        <li>
                            <label id="password-label" for="password-input">Password</label>
                            <input id="password-input" name="password" type="password" placeholder="Please insert your Password" required="required" /><br/><br/>
                        </li>
                        <li>
                            <button type="submit">Log In !</button><br/><br/>
                        </li>

                    </ul>
                </fieldset>
            </form>
        </div>

        <!--header id="header"><xsl:call-template name="header-internet"/></header>

            <section id="form" class="form">
                <article>

                <form id="XaUserLoginFrm" name="XaUserLoginFrm" method="POST" action="?obj=XaUser&amp;evt=XaUserLogin">

					<fieldset>
						<legend style="line-height:2em" ><img height="50vh" src="img/XAllegroLogo.svg" /></legend>
						<ol>
							<li>
								<label id="username-label" for="username-input">Email</label>
								<input id="username-input" name="email" type="email" placeholder="Please insert your Email" required="required" autofocus="autofocus" />
							</li>
							
							<li>
								<label id="password-label" for="password-input">Password</label>
								<input id="password-input" name="password" type="password" placeholder="Please insert your Password" required="required" /><br/><br/>
							</li>
							<li>
								<button type="submit">Log In !</button><br/><br/>
							</li>

						</ol>
					</fieldset>
				</form-->
		<!--div onclick="XaCallAction('','obj=XaUser&amp;evt=XaUserLogin','','POST',false,0,'','XaUserLoginFrm');">pippo</div-->
			<!--/article>
		</section-->

		<!--footer id="footer">
			<xsl:call-template name="footer"/>
		</footer>

		<xsl:if test="$LoginWrong='yes'">
			<script>
				alert('<xsl:value-of select="/root/labels/label[@name='XaUserLoginFrm-Alert-LoginWrong']/disp"/>');
			</script>
		</xsl:if-->
		
		<!--script type="text/javascript">
var html = document.documentElement;
launchFullscreen(html);

		</script-->
    </body>

</html>
</xsl:template>