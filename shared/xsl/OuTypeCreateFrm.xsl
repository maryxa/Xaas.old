<xsl:template match="/">
<xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html></xsl:text>

<html>
	<head>
		<xsl:call-template name="XaGuiHead"/>
	</head>


<!--

CREATE TABLE IF NOT EXISTS `XAllegro`.`XaOuType` (
  `id` INT(9) NOT NULL AUTO_INCREMENT,
  `old_id` INT(9) NULL,
  `name` VARCHAR(256) NULL DEFAULT NULL,
  `description` VARCHAR(1024) NULL DEFAULT NULL,
  `status` INT(1) NULL DEFAULT NULL,
  `created` TIMESTAMP NULL DEFAULT NULL,
  `created_by` INT(9) NULL,
  `time_zone` INT(2) NULL,
  `extension_table` VARCHAR(256) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB
AUTO_INCREMENT = 0
DEFAULT CHARACTER SET = utf8

-->

	<body id="body">
		<header id="header"><xsl:call-template name="XaGuiHeader"/></header>
		<nav id="nav"><xsl:call-template name="XaGuiNav"/></nav>

			<div class="container">

				<form class="form form-1-column" id="XaOuType" name="ChannelAddFrm" enctype="multipart/form-data" method="POST" action="javascript:XaCallAction('','obj=XaOuType&amp;evt=Create','','POST',false,0,'','XaOuType','StringText','','yes','');">

					<fieldset>

						<legend>Aggiungi Tipo di OU </legend>

						<ul>
							<li>
								<label id="XaOuType-Name-label" for="XaAdvChannel-Name">Nome</label>
								<input id="XaOuType-Name" name="XaOuType-Name" type="text" placeholder="inserire il nome della Ou" required="required" autofocus="autofocus" />
							</li>

							<li>
								<label id="XaOuType-Description-label" for="XaOuType-Description">Inserire una descrizione</label>
								<textarea id="XaOuType-Description" name="XaOuType-Description" placeholder="Please insert description" required="required" />
							</li>

							<!-- Template Status -->

						</ul>
					</fieldset>

					<fieldset>
						<button type="reset">Reset</button>
						<button type="submit">Save</button>
					</fieldset>

				</form>
			</div>

	</body>

</html>
</xsl:template>