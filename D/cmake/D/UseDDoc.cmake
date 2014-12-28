# check if the user wants to build ddocs
#
#  Copyright (c) 2007 Tim Burrell <tim.burrell@gmail.com>
#
# All rights reserved.
#
# See LICENSE for details.
#

# Do not build documentation by default
if (NOT CMAKE_D_BUILD_DOCS)
	set(CMAKE_D_BUILD_DOCS False CACHE BOOLEAN TRUE FORCE)
else (NOT CMAKE_D_BUILD_DOCS)
	# check for specified ddoc files
	# default to the candydoc usual
	set(CMAKE_D_BUILD_DOCS True CACHE BOOLEAN FALSE FORCE)	
	if (NOT CMAKE_D_DDOC_FILES)
		set(CMAKE_D_DDOC_FILES "documentation/candydoc/candy.ddoc;documentation/candydoc/modules.ddoc" CACHE STRING FALSE FORCE)
	else (NOT CMAKE_D_DDOC_FILES)
		set(CMAKE_D_DDOC_FILES "${CMAKE_D_DDOC_FILES}" CACHE STRING FALSE FORCE)
	endif (NOT CMAKE_D_DDOC_FILES)

	# copy the candydoc files
	file(GLOB_RECURSE CANDY_DOC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/candydoc/*")
	foreach(item ${CANDY_DOC_FILES})
		string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" item ${item})
		configure_file(${item} ${CMAKE_CURRENT_BINARY_DIR}/documentation/${item} COPYONLY)
	endforeach(item)
	
	# create modules.ddoc
	file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.d")
	set(first True)
	foreach(item ${sources})
		# first make sure we're not config.d
		string(REGEX MATCH "config\\.d" ignore ${item})
		if (NOT ${ignore} MATCHES "")
			# fix up the output
			string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" item ${item})
			string(REGEX REPLACE "\\.d" ".html" htmlFile ${item})
			string(REGEX REPLACE "^.*/" "" htmlFile ${htmlFile})
			string(REGEX REPLACE "\\.d" "" item ${item})
			string(REGEX REPLACE "/" "." item ${item})
			if (first)
				set(modules "${item}")
				set(first False)
				set(CMAKE_D_DDOC_CLEAN_FILES "${CMAKE_CURRENT_BINARY_DIR}/documentation/${htmlFile}" CACHE STRING FALSE FORCE)
			else (first)
				set(modules "${modules};${item}")
				set(CMAKE_D_DDOC_CLEAN_FILES "${CMAKE_D_DDOC_CLEAN_FILES}" "${CMAKE_CURRENT_BINARY_DIR}/documentation/${htmlFile}" CACHE STRING FALSE FORCE)
			endif (first)
		endif (NOT ${ignore} MATCHES "")
	endforeach(item)
	
	# create formatted modules string
	set(modString "MODULES = \n")
	foreach(item ${modules})
		set(modString "${modString}\t$(MODULE ${item})\n")
	endforeach(item)
	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/documentation/candydoc/modules.ddoc" ${modString})

	# create index.html
	set(modString "<html><head><title>${PROJECT_NAME} API Documentation</title></head><body>\n")
	set(modString "<h>${PROJECT_NAME} API Documentation:<br /></h>\n")
	set(modString "${modString}<ul>\n")
	foreach(item ${modules})
		string(REGEX REPLACE "[a-z0-9]*\\." "" filename ${item})
		set(modString "${modString}\t<li> <a href=\"${filename}.html\">${item}</a> </li>\n")
	endforeach(item)
	set(modString "${modString}</ul>\n")
	set(modString "${modString}</body></html>\n")
	file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/documentation/index.html" ${modString})
endif (NOT CMAKE_D_BUILD_DOCS)

