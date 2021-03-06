<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">	
	<html>
	<head>
		<title>Title: <xsl:value-of select="//titre"/></title>
	</head>
	<body>
		<xsl:apply-templates/>
	</body>
	</html>
</xsl:template>

<xsl:template match="titre">
	<h2>
	Title: <xsl:apply-templates />  	
	</h2>
</xsl:template>
	
<xsl:template match="auteur">
	<h3>
		Auteur: <xsl:apply-templates/>
	</h3>
</xsl:template>

<xsl:template match="resume">
	<p>
		Resume:
			<i><xsl:apply-templates /></i>  	
	</p>
</xsl:template>

<xsl:template match="chaptire">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="titre">
	<h4><xsl:apply-templates/></h4>
</xsl:template>

<xsl:template match="section">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="p">
	<p>
		<xsl:apply-templates/>
	</p>
</xsl:template>



</xsl:stylesheet>
