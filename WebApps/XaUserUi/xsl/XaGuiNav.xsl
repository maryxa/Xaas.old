<xsl:template name="XaGuiNav">

<ul class="nav">

	<li id="MenuXaMyPage">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaPages&amp;evt=XaMyPage#MenuXaMyPage">
			<xsl:value-of select="/root/labels/label[@name='Menu-MyPage']/disp"/>
		</a>
	</li>
    <li id="MenuXaWs">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaWs&amp;evt=List&amp;project=MlsClick#MenuXaWs">
			<!--xsl:value-of select="/root/labels/label[@name='Menu-MyPage']/disp"/-->
            Web Services Log
		</a>
	</li>
	
	<li id="MenuXaAdvChannelAddFrm">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaAdv&amp;evt=ChannelAddFrm#MenuXaAdvChannelAddFrm">
			<!--xsl:value-of select="/root/labels/label[@name='Menu-MyPage']/disp"/-->
           Aggiungi canali pubblicita'
		</a>
	</li>
	<li id="MenuXaAdvChannelList">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaAdv&amp;evt=ChannelList#MenuXaAdvChannelList">
			<!--xsl:value-of select="/root/labels/label[@name='Menu-MyPage']/disp"/-->
           Lista canali pubblicita'
		</a>
	</li>
	<li id="MenuXaAdvLeadAddFrm">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaAdv&amp;evt=LeadAddFrm#MenuXaAdvLeadAddFrm">
			<!--xsl:value-of select="/root/labels/label[@name='Menu-MyPage']/disp"/-->
           Aggiungi Report pubblicità
		</a>
	</li>
	<!--li id="MenuXaUserEmployeeSearch" >
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeSearchFrm#MenuXaUserEmployeeSearch">
			<xsl:value-of select="/root/labels/label[@name='Menu-Organization-EmployeeSearch']/disp"/>
		</a>
	</li-->

	<!--li id="MenuXaDataEntry" ><a href="#MenuXaDataEntry"><xsl:value-of select="/root/labels/label[@name='Menu-Organization']/disp"/></a>

		<ul class="sub-menu">

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeVacantList&amp;DefaultFilter=no#MenuXaDataEntry">
					<xsl:value-of select="/root/labels/label[@name='Menu-DataEntry-FillVacantPositions']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeAddFrm#MenuXaDataEntry">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-EmployeeAdd']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserDepartmentAddFrm#MenuXaDataEntry">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-DepartmentAdd']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserCompanyAddFrm#MenuXaDataEntry">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-CompanyAdd']/disp"/>
				</a>
			</li>
		</ul>

	</li>

	<li id="MenuXaUserReports" ><a href="#MenuXaUserReports"><xsl:value-of select="/root/labels/label[@name='Menu-Reports']/disp"/></a>

		<ul class="sub-menu">

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeForecastList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-Forecast']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeActualList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-Actual']/disp"/>
				</a>
			</li>
			
			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserOrgChartView#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-OrganizationChart']/disp"/>
				</a>
			</li>
			
			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeForecastVsActualList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-ActualForecast']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeNewList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-EmployeeNewList']/disp"/>
				</a>
			</li>
			
			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserSalaryChangesList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-SalaryChanges']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeVacantList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-VacantPositions']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeClosedList#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-EmployeeClosedList']/disp"/>
				</a>
			</li>

			<li>
				<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserEmployeeReportPage#MenuXaUserReports">
					<xsl:value-of select="/root/labels/label[@name='Menu-Organization-Print']/disp"/>
				</a>
			</li>
		</ul>

	</li>

	<li id="MenuXaPayment" >
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserEmployee&amp;evt=XaUserSalaryPaymentList#MenuXaPayment">
			<xsl:value-of select="/root/labels/label[@name='Menu-Organization-Payment']/disp"/>
		</a>
	</li>

	<li id="MenuXaUserOrgTreeView">
		<a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserOrgTreeView#MenuXaUserOrgTreeView">
			<xsl:value-of select="/root/labels/label[@name='Menu-Organization-OrganizationTree']/disp"/>
		</a>
	</li>

	<li id="MenuXaSettings"><a href="#MenuXaSettings">Settings</a>

		<ul class="sub-menu">
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLabel&amp;evt=XaLabelGen#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-RefreshLabels']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLabel&amp;evt=XaLabelAddFrm#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-AddLabel']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLabel&amp;evt=XaLabelFromFileAddFrm#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-AddLabelFromFile']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLabel&amp;evt=XaLabelFromXaDomainGen#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-AddXaDomainLabel']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLabel&amp;evt=XaLabelList#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-ListLabel']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaLanguage&amp;evt=XaLanguageList#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-ListLanguage']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaDomain&amp;evt=XaDomainList#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-XaDomainList']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaDomain&amp;evt=XaDomainAddFrm#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-AddXaDomain']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUser&amp;evt=XaUserXaDomainAddFrm#MenuXaSettings"><xsl:value-of select="/root/labels/label[@name='Menu-Translation-AddXaUserXaDomain']/disp"/></a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaCurrency&amp;evt=XaCurrencyRateAddFrm#MenuXaSettings">add exchange rate</a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaCurrency&amp;evt=XaCurrencyRateList#MenuXaSettings">exchange rate list</a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserProfile&amp;evt=XaUserProfileAddFrm#MenuXaSettings">add profile</a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserProfile&amp;evt=XaUserProfileList#MenuXaSettings">profile list</a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserProfile&amp;evt=XaUserProfileXaUserActionAddFrm#MenuXaSettings">manage profile</a></li>

			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserRole&amp;evt=XaUserRoleAddFrm#MenuXaSettings">add role</a></li>
			<li><a onclick='XaCheckUrlReload(this.href)' href="?obj=XaUserRole&amp;evt=XaUserRoleList#MenuXaSettings">role list</a></li>
		</ul>

	</li-->

	<li id="MenuLogout">
		<a href="?obj=XaUserUi&amp;evt=Logout">
			Logout
		</a>
	</li>



	<div class="Logo" onclick="window.open('http://www.xallegro.com')"></div>
</ul>

</xsl:template>