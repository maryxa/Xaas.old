<!--LABEL-->
<xsl:template name="label" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<label>
		<xsl:attribute name="title"><xsl:value-of select="$label-path/help"/></xsl:attribute>
		<xsl:attribute name="for"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="id">label-<xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:value-of select="$label-path/disp"/>
	</label>

</xsl:template>

<!--FROM HELP-->
<xsl:template name="form-help" match="/">

	<xsl:param name="label-path" />

	<div>
		<xsl:attribute name="class">help</xsl:attribute>
		<xsl:attribute name="id">help-<xsl:value-of select="$label-path/disp"/></xsl:attribute>
		<xsl:attribute name="title"><xsl:value-of select="$label-path/help"/></xsl:attribute>
	</div>

</xsl:template>

<!--INPUT TEXT-->
<xsl:template name="input-text" match="/">
	
	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="text">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>

		<xsl:if test="$path/onfocus">
			<xsl:attribute name="onfocus"><xsl:value-of select="$path/onfocus"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/onkeyup">
			<xsl:attribute name="onkeyup"><xsl:value-of select="$path/onkeyup"/></xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/readonly='yes'">
			<xsl:attribute name="readonly">yes</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT EMAIL-->
<xsl:template name="input-email" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="email" pattern="[^ @]*@[^ @]*">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT PASSWORD-->
<xsl:template name="input-password" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="password">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT SELECT-->
<xsl:template name="input-select" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />
	<xsl:param name="onchange-function" />

	<select>

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<!--xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute-->
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="onchange"><xsl:value-of select="$onchange-function"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

		<xsl:for-each select="$path/options/option">
	
			<option>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>

				<xsl:if test="value=$path/value"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>

				<xsl:value-of select="label"/>
			</option>

		</xsl:for-each>

	</select> 

</xsl:template>

<!--INPUT SELECT WITH LABEL-->
<xsl:template name="input-select-with-label" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />
	<xsl:param name="onchange-function" />
	<xsl:param name="default-option-label-path" />

	<select>

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="onchange"><xsl:value-of select="$onchange-function"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

		<option>
			<xsl:attribute name="value"></xsl:attribute>
			--- <xsl:value-of select="$default-option-label-path/disp"/>
		</option>
		
		<xsl:for-each select="$path/options/option">
			<xsl:variable name="label"><xsl:value-of select="label"/></xsl:variable>
			
			<option>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
				<xsl:if test="value=$path/value"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>
				<xsl:value-of select="/root/labels/label[@name=$label]/disp"/>
			</option>

		</xsl:for-each>

	</select> 

</xsl:template>

<!--INPUT SELECT MULTIPLE-->
<xsl:template name="input-select-multiple" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<select>
		
		<xsl:attribute name="multiple">multiple</xsl:attribute>
		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

		<xsl:for-each select="$path/options/option">
	
			<option>
				<xsl:attribute name="value"><xsl:value-of select="value"/></xsl:attribute>
				<xsl:if test="value=$path/values/*[name()='value']"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>
				<xsl:value-of select="label"/>
			</option>

		</xsl:for-each>

	</select> 

</xsl:template>

<!--INPUT DATE-->
<xsl:template name="input-date" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<!--xsl:variable name="year_value" select="substring($path/value,1,4)"/>
	<xsl:variable name="month_value" select="substring($path/value,6,2)"/-->

	<xsl:variable name="year_value"  select="$path/value/date/year"/>
	<xsl:variable name="month_value" select="$path/value/date/month"/>

	<select class="DateTime">
		<xsl:attribute name="id"><xsl:value-of select="$path/id"/>_day</xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/>_day</xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<option value="">---</option>

		<xsl:variable name="day_to">
			<xsl:choose>
			<xsl:when test="$month_value='04'">30</xsl:when>
			<xsl:when test="$month_value='06'">30</xsl:when>
			<xsl:when test="$month_value='09'">30</xsl:when>
			<xsl:when test="$month_value='11'">30</xsl:when>
			<xsl:when test="$month_value='02' and $year_value mod 4 =0">29</xsl:when>
			<xsl:when test="$month_value='02' and $year_value mod 4!=0">28</xsl:when>
			<xsl:otherwise>31</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:call-template name="add-days-options">
			<xsl:with-param name="day_to" select="$day_to"/>
			<xsl:with-param name="cur_day" select="1"/>
			<xsl:with-param name="value" select="$path/value/date/day"/>
		</xsl:call-template>
	</select>

	<select class="DateTime">
		<xsl:attribute name="id"><xsl:value-of select="$path/id"/>_month</xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/>_month</xsl:attribute>
		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="onchange">javascript:AddDaysOptionsToSelect('<xsl:value-of select="$path/id"/>');</xsl:attribute>

		<option value="">---</option>
		<option value="01"><xsl:if test="$month_value='01'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Jan</option>
		<option value="02"><xsl:if test="$month_value='02'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Feb</option>
		<option value="03"><xsl:if test="$month_value='03'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Mar</option>
		<option value="04"><xsl:if test="$month_value='04'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Apr</option>
		<option value="05"><xsl:if test="$month_value='05'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>May</option>
		<option value="06"><xsl:if test="$month_value='06'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Jun</option>
		<option value="07"><xsl:if test="$month_value='07'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Jul</option>
		<option value="08"><xsl:if test="$month_value='08'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Aug</option>
		<option value="09"><xsl:if test="$month_value='09'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Sep</option>
		<option value="10"><xsl:if test="$month_value='10'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Oct</option>
		<option value="11"><xsl:if test="$month_value='11'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Nov</option>
		<option value="12"><xsl:if test="$month_value='12'"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>Dec</option>
	</select>

	<select class="DateTime">
		<xsl:attribute name="id"><xsl:value-of select="$path/id"/>_year</xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/>_year</xsl:attribute>
		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<!--xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute-->
		<xsl:attribute name="onchange">javascript:AddDaysOptionsToSelect('<xsl:value-of select="$path/id"/>')</xsl:attribute>

		<option value="">---</option>

		<xsl:call-template name="add-years-options">
			<xsl:with-param name="year_to" select="$path/year_to"/>
			<xsl:with-param name="cur_year" select="$path/year_from"/>
			<xsl:with-param name="value" select="$year_value"/>
		</xsl:call-template>
	</select>

</xsl:template>


<!--INPUT TIME-->
<xsl:template name="input-time" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="time">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT MONEY-->
<xsl:template name="input-money" match="/">
	
	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="text">

		<xsl:attribute name="pattern">^((\d+)|(\d{1,3})(\,\d{3}|)*)(\.\d{2}|)$</xsl:attribute>

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="value">
			<xsl:call-template name="format-money-view">
				<xsl:with-param name="value" select="$path/value"/>
				<xsl:with-param name="with_cents">yes</xsl:with-param>
			</xsl:call-template>
		</xsl:attribute>
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/onfocus">
			<xsl:attribute name="onfocus"><xsl:value-of select="$path/onfocus"/></xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/onkeyup">
			<xsl:attribute name="onkeyup"><xsl:value-of select="$path/onkeyup"/></xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/readonly='yes'">
			<xsl:attribute name="readonly">yes</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT RATE-->
<xsl:template name="input-rate" match="/">
	
	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="text">

		<xsl:attribute name="pattern">^(\d{1,3})(\.\d{1,8})?$</xsl:attribute>

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>
		
		<xsl:if test="$path/disabled='yes'">
			<xsl:attribute name="disabled">yes</xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/onfocus">
			<xsl:attribute name="onfocus"><xsl:value-of select="$path/onfocus"/></xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>
		<xsl:if test="$path/readonly='yes'">
			<xsl:attribute name="readonly">yes</xsl:attribute>
		</xsl:if>

		<xsl:if test="$path/onkeyup">
			<xsl:attribute name="onkeyup"><xsl:value-of select="$path/onkeyup"/></xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT TEXTAREA-->
<xsl:template name="input-textarea" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<textarea>

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<!--xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute-->
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>
		<xsl:value-of select="$path/value"/>
	</textarea>

</xsl:template>


<!--INPUT NUMBER-->
<xsl:template name="input-number" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="number">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>
		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>

	</input>

</xsl:template>

<!--INPUT CHECKBOX-->
<xsl:template name="input-checkbox" match="/">

	<xsl:param name="path" />
	<xsl:param name="label-path" />

	<input type="checkbox">

		<xsl:attribute name="id"><xsl:value-of select="$path/id"/></xsl:attribute>
		<xsl:attribute name="name"><xsl:value-of select="$path/name"/></xsl:attribute>
		<xsl:attribute name="placeholder"><xsl:value-of select="$label-path/placeholder"/></xsl:attribute>
		<xsl:attribute name="value"><xsl:value-of select="$path/value"/></xsl:attribute>

		<xsl:if test="$path/required='yes'">
			<xsl:attribute name="required">true</xsl:attribute>
		</xsl:if>

		<xsl:attribute name="maxlength"><xsl:value-of select="$path/maxlength"/></xsl:attribute>
		<xsl:attribute name="size"><xsl:value-of select="$path/size"/></xsl:attribute>

		<xsl:attribute name="class"><xsl:value-of select="$path/class"/></xsl:attribute>
		<xsl:if test="$path/checked='true'"><xsl:attribute name="checked">checked</xsl:attribute></xsl:if>

	</input>

</xsl:template>

<!--LEGEND-->
<xsl:template name="legend" match="/">

	<xsl:param name="label-path" />

	<legend>
		<xsl:value-of select="$label-path"/>
	</legend>

</xsl:template>

<!--FOLDER-->
<xsl:template name="folder">
	<xsl:param name="path"/>

	<li>
		<label for="{id}"><xsl:value-of select="name"/></label>
		<input type="checkbox" id="{id}" /> 
		<ol>
			<xsl:for-each select="*">
				<xsl:if test="name()='folder'">
					<xsl:call-template name="folder">
						<xsl:with-param name="path" select="."/>
					</xsl:call-template>
				</xsl:if>
				<xsl:if test="name()='file'">
					<xsl:call-template name="file">
						<xsl:with-param name="path" select="."/>
					</xsl:call-template>
				</xsl:if>
			</xsl:for-each>
		</ol>
	</li>

</xsl:template>

<!--FILE-->
<xsl:template name="file">
	<xsl:param name="path"/>
		<li class="file"><a href=""><xsl:value-of select="name"/></a></li>
</xsl:template>

<!--obj=XaUser&evt=XaUserCompanyView&RowId=FZcVEWGh9i7c9bwGRjvg2g==-->
<!--TREE-OU-->
<xsl:template name="tree-ou">
	<xsl:param name="path"/>

	<xsl:param name="action-ou"/><!-- non usata -->
	<xsl:param name="action-user"/>

	<xsl:variable name="action">
		<xsl:if test="user_type=1">XaUserCompanyView</xsl:if>
		<xsl:if test="user_type=2">XaUserDepartmentView</xsl:if>
	</xsl:variable>

	<li>
		<label title="click for employee list">
			<xsl:attribute name="for"><xsl:value-of select="id"/></xsl:attribute>
			<a href="#MenuXaOrganization" title="click for organizational unit details" onclick="XaCallAction('','obj=XaUser&amp;evt={$action}&amp;RowId={id}','detail','POST',true,1,'detail','','StringHtml');"></a>
			<xsl:value-of select="name"/>
		</label>
		<input type="checkbox" id="{id}" title="click for employee list"> 
			<xsl:attribute name="onclick">XaCallAction('','obj=XaUserEmployee&amp;evt=XaUserEmployeeList&amp;LayoutType=Included&amp;tree_parent_ID=<xsl:value-of select="id"/>&amp;LoginFilter='+document.getElementById('LoginFilter').checked,'detail','POST',true,1,'detail','','StringHtml'); </xsl:attribute>
		</input>
		<ol>
			<xsl:for-each select="*">
				<xsl:if test="name()='ou'">
					
					<xsl:call-template name="tree-ou">

						<xsl:with-param name="path" select="."/>
						<xsl:with-param name="action-ou" select="$action-ou"/>
						<xsl:with-param name="action-user" select="$action-user"/>

					</xsl:call-template>

				</xsl:if>

				<xsl:if test="name()='user'">
					
					<xsl:call-template name="tree-user">

						<xsl:with-param name="path" select="."/>
						<xsl:with-param name="action-user" select="$action-user"/>

					</xsl:call-template>

				</xsl:if>
			</xsl:for-each>
		</ol>
	</li>

</xsl:template>

<!--TREE-USER-->
<xsl:template name="tree-user">
	<xsl:param name="path"/>
	<xsl:param name="action-user"/>

		<li class="file">
			<a>
				<xsl:attribute name="href">javascript:XaCallAction('','obj=XaUserEmployee&amp;evt=<xsl:value-of select="$action-user" />&amp;RowId=<xsl:value-of select="id"/>','detail','POST',true,1,'detail','','StringHtml','yes');</xsl:attribute>
				<xsl:value-of select="name"/>
			</a>
		</li>
</xsl:template>




<!--CHART-OU-->
<xsl:template name="chart-ou">
	<xsl:param name="path"/>

	<xsl:param name="action-ou"/>
	<xsl:param name="action-user"/>

	<li>
		<!--
		<label>
		<xsl:attribute name="for"><xsl:value-of select="id"/></xsl:attribute>
		<xsl:attribute name="onclick">XaCallAction('','obj=XaUser&amp;evt=<xsl:value-of select="$action-ou" />&amp;RowId=<xsl:value-of select="id"/>','detail','POST',true,1,'detail','','StringHtml');</xsl:attribute>
		<xsl:value-of select="name"/>
		</label>
		<input type="checkbox" id="{id}" /> 
		-->

			<a href="">
				<b><xsl:value-of select="name" /></b>
			<br/>

			</a>

		<ul>

			<xsl:for-each select="*">
				<xsl:if test="name()='ou'">
					
					<xsl:call-template name="chart-ou">

						<xsl:with-param name="path" select="."/>
						<xsl:with-param name="action-ou" select="$action-ou"/>
						<xsl:with-param name="action-user" select="$action-user"/>

					</xsl:call-template>

				</xsl:if>

				<xsl:if test="name()='user'">
					
					<xsl:call-template name="chart-user">

						<xsl:with-param name="path" select="."/>
						<xsl:with-param name="action-user" select="$action-user"/>

					</xsl:call-template>

				</xsl:if>
			</xsl:for-each>
		</ul>
	</li>

</xsl:template>




<!--CHART-USER-->
<xsl:template name="chart-user">
	<xsl:param name="path"/>
		<li>
			<a href="#" onclick="XaCallAction('','obj=XaUserEmployee&amp;evt=XaUserEmployeeView&amp;RowId={id}','ModalContent','POST',true,0,'','','StringHtml','yes');XaFieldSetCssPropertyById('ModalWindow','opacity:1;pointer-events:auto;');">
				<b><xsl:value-of select="name" /></b>
				<br/>
				<xsl:value-of select="department" />
				<br/>
				<xsl:value-of select="jobtitle" />
				<br/>
			</a>

			<xsl:if test="user">
			<ul>

				<xsl:for-each select="*[name()='user']">
					<xsl:call-template name="chart-user">
						<xsl:with-param name="path" select="."/>
					</xsl:call-template>
				</xsl:for-each>
			</ul>
			</xsl:if>

		</li>
</xsl:template>

<!--SORTER TABLE THEAD-->
<xsl:template name="sorter-thead">

	<xsl:param name="path"/>

	<xsl:for-each select="$path">
		<xsl:variable name="name"><xsl:value-of select="name"/></xsl:variable>
		<!--th onclick="XaSortTable('sorter','text','DESC','0','0')"-->		
		<th>
			<xsl:if test="ordertype!='nothing'">
				<xsl:attribute name="onclick">XaSortTable('sorter','<xsl:value-of select="ordertype"/>','DESC','0','<xsl:value-of select="position()-1"/>')</xsl:attribute>
			</xsl:if>
			<!--xsl:attribute name="class"><xsl:value-of select="class"/></xsl:attribute-->
			<xsl:value-of select="/root/labels/label[@name=$name]/disp"/>
			<!--xsl:value-of select="name"/-->
		</th>

	</xsl:for-each>

</xsl:template>

<!--SELECT ACTION LIST-->
<xsl:template name="list-select-action">

<!--AUTOMATIZZARE IL TARGET CON VARIABILE-->
	<select class="dropdown">
		<xsl:attribute name="onchange">XaCallAction('',this.options[this.selectedIndex].value,'ModalContent','POST',true,0,'','','StringHtml','yes');XaFieldSetCssPropertyById('ModalWindow','opacity:1;pointer-events:auto;');</xsl:attribute>

		<option value=""><xsl:value-of select="/root/labels/label[@name='Actions']/disp"/></option>
		<xsl:for-each select="./actions/action">
		<xsl:variable name="label"><xsl:value-of select="label"/></xsl:variable>
			<option>
				<xsl:attribute name="value">obj=<xsl:value-of select="object"/>&amp;evt=<xsl:value-of select="event"/>&amp;RowId=<xsl:value-of select="id"/></xsl:attribute>
				<xsl:value-of select="/root/labels/label[@name=$label]/disp"/>
				<!--xsl:value-of select="label"/-->
			</option>
		</xsl:for-each>
	</select>

</xsl:template>

<!--MODAL WINDOW-->
<xsl:template name="modal-window">
	<div id="ModalWindow" class="modal">
		<div id="ModalDiv">
			<a href="#MenuXaOrganization" title="Close" class="close" onclick="XaFieldSetCssPropertyModal('ModalWindow','opacity:0');">X</a>
			<div id="ModalContent"></div>
		</div>
	</div>
</xsl:template>

<!--VIEW-MAIL-LINK-->
<xsl:template name="view-mail-link" match="/">

	<xsl:param name="path" />

	<a href="mailto:{$path}">
		<xsl:value-of select="$path"/>
	</a>

</xsl:template>

<!--VIEW-FIELD>
<xsl:template name="view-field" match="/">

	<xsl:param name="path" />

	<label>
		<xsl:value-of select="$path"/>
	</label>

</xsl:template-->


<xsl:template name="add-years-options">
	<xsl:param name="year_to"/>
	<xsl:param name="cur_year"/>
	<xsl:param name="value"/>

	<option value="{$cur_year}">
		<xsl:if test="$value=$cur_year"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>
		<xsl:value-of select="$cur_year"/>
	</option>

	<xsl:if test="$cur_year &lt; $year_to">
		<xsl:call-template name="add-years-options">
			<xsl:with-param name="year_to" select="$year_to"/>
			<xsl:with-param name="cur_year" select="$cur_year +1"/>
			<xsl:with-param name="value" select="$value"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<xsl:template name="add-days-options">
	<xsl:param name="day_to"/>
	<xsl:param name="cur_day"/>
	<xsl:param name="value"/>

	<option>
		<xsl:attribute name="value">
		<xsl:choose>
			<xsl:when test="$cur_day &gt;9"><xsl:value-of select="$cur_day"/></xsl:when>
			<xsl:otherwise>0<xsl:value-of select="$cur_day"/></xsl:otherwise>
		</xsl:choose>
		</xsl:attribute>

		<xsl:if test="$value=$cur_day"><xsl:attribute name="selected">yes</xsl:attribute></xsl:if>

		<xsl:value-of select="$cur_day"/>
	</option>

	<xsl:if test="$cur_day &lt; $day_to">
		<xsl:call-template name="add-days-options">
			<xsl:with-param name="day_to" select="$day_to"/>
			<xsl:with-param name="cur_day" select="$cur_day +1"/>
			<xsl:with-param name="value" select="$value"/>
		</xsl:call-template>
	</xsl:if>
</xsl:template>

<xsl:template name="format-money">	<!-- usata nella input, non mette separatore migliaia -->
	<xsl:param name="value"/>
	<!--xsl:param name="format"/-->

	<xsl:choose>
	<xsl:when test="contains($value,'.')">
		<xsl:value-of select="substring-before($value,'.')"/>.<xsl:value-of select="substring(substring-after($value,'.'),1,2)"/>
	</xsl:when>
	<xsl:otherwise><xsl:value-of select="$value"/>.00</xsl:otherwise>
	</xsl:choose>
</xsl:template>


<xsl:template name="format-money-view">		<!-- usata in view/list, aggiunge separatore migliaia -->
	<xsl:param name="value"/>
	<xsl:param name="with_cents"/>
	<!--xsl:param name="format"/-->


<xsl:if test="$value!=''">

	<xsl:variable name="absvalue">
		<xsl:choose>
			<xsl:when test="$value &gt; 0"><xsl:value-of select="$value"/></xsl:when>
			<xsl:otherwise><xsl:value-of select="-1 * $value"/></xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="cents">
		<xsl:choose>
			<xsl:when test="contains($absvalue,'.')">
				<xsl:value-of select="substring(substring-after($absvalue,'.'),1,2)"/>
			</xsl:when>
			<xsl:otherwise>00</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="integer">
		<xsl:choose>
			<xsl:when test="contains($absvalue,'.')">
				<xsl:value-of select="substring-before($absvalue,'.')"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$absvalue"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:variable>
	<xsl:variable name="ilength" select="string-length($integer)"/>

	<xsl:if test="$value &lt; 0">-</xsl:if>
	<xsl:choose>
		<xsl:when test="$absvalue &gt;= 1000000">
			<xsl:value-of select="substring($integer,1,$ilength -6)"/>,<xsl:value-of select="substring($integer,$ilength -5,3)"/>,<xsl:value-of select="substring($integer,$ilength -2,3)"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:choose>
				<xsl:when test="$absvalue &gt;= 1000">
					<xsl:value-of select="substring($integer,1,$ilength -3)"/>,<xsl:value-of select="substring($integer,$ilength -2,3)"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="$integer"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:otherwise>
	</xsl:choose>

	<xsl:if test="$with_cents='yes'">.<xsl:value-of select="$cents"/></xsl:if>

</xsl:if>

</xsl:template>


<xsl:template name="format-money-report">		<!-- usata in report -->
	<xsl:param name="value"/>
	<xsl:param name="with_cents"/>

	<xsl:choose>
	<xsl:when test="$value='0'">-&#160;&#160;&#160;</xsl:when>
	<xsl:otherwise>
		<xsl:call-template name="format-money-view">
			<xsl:with-param name="value" select="$value"/>
			<xsl:with-param name="with_cents">no</xsl:with-param>
		</xsl:call-template>
	</xsl:otherwise>
	</xsl:choose>
</xsl:template>


<xsl:template name="format-date-view">		<!-- usata in view/list -->
	<xsl:param name="value"/>

	<xsl:variable name="month" select="$value/date/month"/>
	<xsl:variable name="month_name">
		<xsl:if test="$month='01'">Jan</xsl:if>
		<xsl:if test="$month='02'">Feb</xsl:if>
		<xsl:if test="$month='03'">Mar</xsl:if>
		<xsl:if test="$month='04'">Apr</xsl:if>
		<xsl:if test="$month='05'">May</xsl:if>
		<xsl:if test="$month='06'">Jun</xsl:if>
		<xsl:if test="$month='07'">Jul</xsl:if>
		<xsl:if test="$month='08'">Aug</xsl:if>
		<xsl:if test="$month='09'">Sep</xsl:if>
		<xsl:if test="$month='10'">Oct</xsl:if>
		<xsl:if test="$month='11'">Nov</xsl:if>
		<xsl:if test="$month='12'">Dec</xsl:if>
	</xsl:variable>

	<xsl:value-of select="$value/date/day"/>&#160;<xsl:value-of select="$month_name"/>&#160;<xsl:value-of select="$value/date/year"/>

</xsl:template>


<xsl:template name="format-date-view-from-string">
	<xsl:param name="value"/>

	<xsl:variable name="month" select="substring($value,6,2)"/>
	<xsl:variable name="month_name">
		<xsl:if test="$month='01'"><xsl:value-of select="/root/labels/label[@name='Jan']/disp"/></xsl:if>
		<xsl:if test="$month='02'"><xsl:value-of select="/root/labels/label[@name='Feb']/disp"/></xsl:if>
		<xsl:if test="$month='03'"><xsl:value-of select="/root/labels/label[@name='Mar']/disp"/></xsl:if>
		<xsl:if test="$month='04'"><xsl:value-of select="/root/labels/label[@name='Apr']/disp"/></xsl:if>
		<xsl:if test="$month='05'"><xsl:value-of select="/root/labels/label[@name='May']/disp"/></xsl:if>
		<xsl:if test="$month='06'"><xsl:value-of select="/root/labels/label[@name='Jun']/disp"/></xsl:if>
		<xsl:if test="$month='07'"><xsl:value-of select="/root/labels/label[@name='Jul']/disp"/></xsl:if>
		<xsl:if test="$month='08'"><xsl:value-of select="/root/labels/label[@name='Aug']/disp"/></xsl:if>
		<xsl:if test="$month='09'"><xsl:value-of select="/root/labels/label[@name='Sep']/disp"/></xsl:if>
		<xsl:if test="$month='10'"><xsl:value-of select="/root/labels/label[@name='Oct']/disp"/></xsl:if>
		<xsl:if test="$month='11'"><xsl:value-of select="/root/labels/label[@name='Nov']/disp"/></xsl:if>
		<xsl:if test="$month='12'"><xsl:value-of select="/root/labels/label[@name='Dec']/disp"/></xsl:if>
	</xsl:variable>

	<xsl:value-of select="substring($value,9,2)"/>&#160;<xsl:value-of select="$month_name"/>&#160;<xsl:value-of select="substring($value,1,4)"/>

</xsl:template>


<xsl:template name="format-date-report-from-string">
	<xsl:param name="value"/>

	<xsl:variable name="month" select="substring($value,6,2)"/>
	<xsl:variable name="month_name">
		<xsl:if test="$month='01'">jan</xsl:if>
		<xsl:if test="$month='02'">feb</xsl:if>
		<xsl:if test="$month='03'">mar</xsl:if>
		<xsl:if test="$month='04'">apr</xsl:if>
		<xsl:if test="$month='05'">may</xsl:if>
		<xsl:if test="$month='06'">jun</xsl:if>
		<xsl:if test="$month='07'">jul</xsl:if>
		<xsl:if test="$month='08'">aug</xsl:if>
		<xsl:if test="$month='09'">sep</xsl:if>
		<xsl:if test="$month='10'">oct</xsl:if>
		<xsl:if test="$month='11'">nov></xsl:if>
		<xsl:if test="$month='12'">dec</xsl:if>
	</xsl:variable>

	<xsl:value-of select="substring($value,9,2)"/>-<xsl:value-of select="$month_name"/>-<xsl:value-of select="substring($value,1,4)"/>

</xsl:template>

<xsl:template name="month_name">
	<xsl:param name="value"/>

	<xsl:if test="$value='01'">jan</xsl:if>
	<xsl:if test="$value='02'">feb</xsl:if>
	<xsl:if test="$value='03'">mar</xsl:if>
	<xsl:if test="$value='04'">apr</xsl:if>
	<xsl:if test="$value='05'">may</xsl:if>
	<xsl:if test="$value='06'">jun</xsl:if>
	<xsl:if test="$value='07'">jul</xsl:if>
	<xsl:if test="$value='08'">aug</xsl:if>
	<xsl:if test="$value='09'">sep</xsl:if>
	<xsl:if test="$value='10'">oct</xsl:if>
	<xsl:if test="$value='11'">nov></xsl:if>
	<xsl:if test="$value='12'">dec</xsl:if>

</xsl:template>