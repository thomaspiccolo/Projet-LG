<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="rapport">	
	<html>
	<head>
		<title>Title: TP Analyseur XML</title>
	</head>
	<body>
		<h1> Fichier de Sortie HTML du TP Analyseur XML </h1>
		<xsl:apply-templates/>
		<p> Bla Bla </p>
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

<xsl:template match="section">
	<xsl:apply-templates/>
</xsl:template>

<xsl:template match="p">
	<p>
		<xsl:apply-templates/>
	</p>
</xsl:template>



</xsl:stylesheet>
