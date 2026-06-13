# Script that synchronizes the local test data
#
# Version: 20260608

$Repository = "log2timeline/dfvfs"
$TestDataPath = "test_data"
$TestSet = "public"
$TestInputDirectory = "tests\input"
$TestFiles = "ext2.raw ext4.raw"

If (-Not (Test-Path ${TestInputDirectory}))
{
	New-Item -Name ${TestInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestInputDirectory}\.fsextinfo_sh"))
{
	New-Item -Name "${TestInputDirectory}\.fsextinfo_sh" -ItemType "directory" | Out-Null
	Write-Output "-H" | Out-File -Encoding ascii -FilePath "${TestInputDirectory}\.fsextinfo_sh\options"
}
If (-Not (Test-Path "${TestInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$UrlTestFile = [System.Uri]::EscapeDataString("${TestFile}")
	$Url = "https://raw.githubusercontent.com/${Repository}/refs/heads/main/${TestDataPath}/${UrlTestFile}"

	$ProgressPreference = 'SilentlyContinue'
	Invoke-WebRequest -Uri ${Url} -OutFile "${TestInputDirectory}\${TestSet}\${TestFile}"
}

