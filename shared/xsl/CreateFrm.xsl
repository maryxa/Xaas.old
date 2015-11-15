<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html id="html">

    <head>
        <xsl:call-template name="XaGuiHead"/>
    </head>

    <body id="body">
		<header id="header"><xsl:call-template name="XaGuiHeader"/></header>

                <script>getelement</script>
        <!--div class="container">

            <form style="height:99%" class="form form-1-column" id="Login" name="Login" method="POST" action="?obj=XaUserUi&amp;evt=Login">

                <fieldset id="XaOuType" name="XaOuType">



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
        </div-->

    </body>

</html>
</xsl:template>