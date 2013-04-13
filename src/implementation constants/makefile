#
#	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
#
#	This file is part of Implementation-dependent Constants.
#
#	Implementation-dependent Constants is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	Implementation-dependent Constants is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with Implementation-dependent Constants.  If not, see <http://www.gnu.org/licenses/>.
#

EXECUTABLE_NAME = implementation\ constants

CPP_COMPILER = g++
CPP_FLAGS = -Wall -O3
CPP_LIBRARIES = -lGLU -lGLEW -lglut

GENERATED_FILE = main.cpp
GENERATOR = gawk
GENERATOR_SCRIPT = generator.awk
BASE_SOURCE = main-base.cpp
GENERATOR_INPUT = table.txt



all:	$(EXECUTABLE_NAME)

clean:
		rm $(GENERATED_FILE)

distclean:	clean
		rm $(EXECUTABLE_NAME)



$(EXECUTABLE_NAME): $(GENERATED_FILE)
		$(CPP_COMPILER) $(CPP_FLAGS) $(CPP_LIBRARIES) $(GENERATED_FILE) -o $(EXECUTABLE_NAME)

$(GENERATED_FILE): $(GENERATOR_SCRIPT) $(BASE_SOURCE) $(GENERATOR_INPUT)
		$(GENERATOR) -f $(GENERATOR_SCRIPT) -v BASE=$(BASE_SOURCE) < $(GENERATOR_INPUT) > $(GENERATED_FILE)


.PHONY: all clean distclean
