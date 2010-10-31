BEGIN {
	while(getline line < BASE > 0)
	{
		if(line ~ /\/\* %--% \*\//)
			break;
		print line;
	} # end while
	
	FS = "\t";
} # end BEGIN pattern


/^[\t ]*$/ {
	# ignore
}


/^GL_/ && $3 == "int"{
	print "\tglGetIntegerv(" $1 ",&ival);";
	print "\tif(glGetError() == GL_NO_ERROR)";
	print "\t\tcout << setw(W) << esquape(" $1 ") << setw(15) << " $2 " << ival << '\\n';";
}


/^GL_/ && $3 == "float"{
	print "\tglGetFloatv(" $1 ",&fval);";
	print "\tif(glGetError() == GL_NO_ERROR)";
	print "\t\tcout << setw(W) << esquape(" $1 ") << setw(15) << " $2 " << fval << '\\n';";
}


/^GL_/ && $3 == "bool"{
	print "\tglGetBooleanv(" $1 ",&bval);";
	print "\tif(glGetError() == GL_NO_ERROR)";
	print "\t\tcout << setw(W) << esquape(" $1 ") << setw(15) << '-' << (bval?\"yes\":\"no\") << '\\n';";
}


/^GL_/ && $3 == "int-2"{
	print "\tglGetIntegerv(" $1 ",iv);";
	print "\tif(glGetError() == GL_NO_ERROR)";
	print "\t\tcout << setw(W) << esquape(" $1 ") << setw(15) << \"" $2 "\" << iv[0] << ',' << iv[1] << '\\n';";
}


/^GL_/ && $3 == "float-2"{
	print "\tglGetFloatv(" $1 ",fv);";
	print "\tif(glGetError() == GL_NO_ERROR)";
	print "\t\tcout << setw(W) << esquape(" $1 ") << setw(15) << \"" $2 "\" << fv[0] << ',' << fv[1] << '\\n';";
}


/^GL_/ && $3 == "string"{
	print "\tsval = glGetString(" $1 ");";
	print "\tif(glGetError() == GL_NO_ERROR && sval != NULL)";
	print "\t\tcout << setw(W-15) << esquape(" $1 ") \":\" << sval << '\\n';";
}


/^GLU_/ && $3 == "gluString"{
	print "\tcout << setw(W-15) << esquape(" $1 ") \":\" << gluGetString(" $1 ") << '\\n';";
}


/^GL_/ && $3 == "convolution"{
	print "\tif(glGetConvolutionParameteriv)";
	print "\t{";
	print "\t\tglGetConvolutionParameteriv(" $4 "," $1 ",&ival);";
	print "\t\tif(glGetError() == GL_NO_ERROR)";
	print "\t\t\tcout << setw(W) << esquape(" $4 ":" $1 ") << setw(15) << " $2 " << ival << '\\n';";
	print "\t} // end if";
}


/^GL_/ && $3 == "query"{
	print "\tif(glGetQueryiv)";
	print "\t{";
	print "\t\tglGetQueryiv(" $4 "," $1 ",&ival);";
	print "\t\tif(glGetError() == GL_NO_ERROR)";
	print "\t\t\tcout << setw(W) << esquape(" $4 ":" $1 ") << setw(15) << " $2 " << ival << '\\n';";
	print "\t} // end if";
}


/^\$/ {
	while(getline line < BASE > 0)
	{
		if(line ~ /\/\* %--% \*\//)
			break;
		print line;
	} # end while
}


/^#/ {
	print "\tcout << '\\n' << setw(W) << \"state variable\" << setw(15) << \"minimum value\" << \"actual value\\n\";";
}


/^@/ {
	print "\n\tcout << \"\\n\\n\" esquape(" substr($0,2) ") \"\\n\\n\";";
}


/^%/ {
	print "\n\tcout << \"\\n\\n\" esquape(" substr($0,2) ") \"\\n\\n\";";
	print "\tcout << setw(W) << \"state variable\" << setw(15) << \"minimum value\" << \"actual value\\n\";";
}


END {
	while(getline line < BASE > 0)
		print line;
} # end END pattern