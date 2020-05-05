###############################################################################
#
# $URL$
# $Id$
#
# Description       : CMake build script for libSBML dependencies (xerces)
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2011 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################

if (WITH_XERCES)
project (xerces)

if (WITH_STATIC_RUNTIME)
	foreach(flag_var
		CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
		CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

		if(${flag_var} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
		endif(${flag_var} MATCHES "/MD")
		
		
	endforeach(flag_var)
	add_definitions( -D_MT)
endif(WITH_STATIC_RUNTIME)

file(GLOB XERCES_SOURCE
	 "src/xercesc/util/NetAccessors/BinHTTPInputStreamCommon.cpp" 
    "src/xercesc/util/NetAccessors/WinSock/BinHTTPURLInputStream.cpp" 
    "src/xercesc/util/NetAccessors/WinSock/WinSockNetAccessor.cpp" 
    "src/xercesc/util/regx/ASCIIRangeFactory.cpp" 
    "src/xercesc/util/regx/BlockRangeFactory.cpp" 
    "src/xercesc/util/regx/BMPattern.cpp" 
    "src/xercesc/util/regx/CharToken.cpp" 
    "src/xercesc/util/regx/ClosureToken.cpp" 
    "src/xercesc/util/regx/ConcatToken.cpp" 
    "src/xercesc/util/regx/Match.cpp" 
    "src/xercesc/util/regx/Op.cpp" 
    "src/xercesc/util/regx/OpFactory.cpp" 
    "src/xercesc/util/regx/ParenToken.cpp" 
    "src/xercesc/util/regx/ParserForXMLSchema.cpp" 
    "src/xercesc/util/regx/RangeFactory.cpp" 
    "src/xercesc/util/regx/RangeToken.cpp" 
    "src/xercesc/util/regx/RangeTokenMap.cpp" 
    "src/xercesc/util/regx/RegularExpression.cpp" 
    "src/xercesc/util/regx/RegxParser.cpp" 
    "src/xercesc/util/regx/RegxUtil.cpp" 
    "src/xercesc/util/regx/StringToken.cpp" 
    "src/xercesc/util/regx/Token.cpp" 
    "src/xercesc/util/regx/TokenFactory.cpp" 
    "src/xercesc/util/regx/UnicodeRangeFactory.cpp" 
    "src/xercesc/util/regx/UnionToken.cpp" 
    "src/xercesc/util/regx/XMLRangeFactory.cpp" 
    "src/xercesc/util/regx/XMLUniCharacter.cpp" 
    "src/xercesc/util/FileManagers/WindowsFileMgr.cpp" 
    "src/xercesc/util/MutexManagers/WindowsMutexMgr.cpp" 
	"src/xercesc/util/*.cpp"
	"src/xercesc/util/MsgLoaders/Win32/Win32MsgLoader.cpp"
	"src/xercesc/util/Transcoders/Win32/Win32TransService.cpp"
    "src/xercesc/framework/LocalFileFormatTarget.cpp" 
    "src/xercesc/framework/LocalFileInputSource.cpp" 
    "src/xercesc/framework/MemBufFormatTarget.cpp" 
    "src/xercesc/framework/MemBufInputSource.cpp" 
    "src/xercesc/framework/StdInInputSource.cpp" 
    "src/xercesc/framework/StdOutFormatTarget.cpp" 
    "src/xercesc/framework/URLInputSource.cpp" 
    "src/xercesc/framework/Wrapper4DOMLSInput.cpp" 
    "src/xercesc/framework/Wrapper4InputSource.cpp" 
    "src/xercesc/framework/XMLAttDef.cpp" 
    "src/xercesc/framework/XMLAttDefList.cpp" 
    "src/xercesc/framework/XMLAttr.cpp" 
    "src/xercesc/framework/XMLBuffer.cpp" 
    "src/xercesc/framework/XMLBufferMgr.cpp" 
    "src/xercesc/framework/XMLContentModel.cpp" 
    "src/xercesc/framework/XMLDTDDescription.cpp" 
    "src/xercesc/framework/XMLElementDecl.cpp" 
    "src/xercesc/framework/XMLEntityDecl.cpp" 
    "src/xercesc/framework/XMLFormatter.cpp" 
    "src/xercesc/framework/XMLGrammarDescription.cpp" 
    "src/xercesc/framework/XMLGrammarPoolImpl.cpp" 
    "src/xercesc/framework/XMLNotationDecl.cpp" 
    "src/xercesc/framework/XMLRecognizer.cpp" 
    "src/xercesc/framework/XMLRefInfo.cpp" 
    "src/xercesc/framework/XMLSchemaDescription.cpp" 
    "src/xercesc/framework/XMLValidator.cpp" 
    "src/xercesc/framework/psvi/PSVIAttribute.cpp" 
    "src/xercesc/framework/psvi/PSVIAttributeList.cpp" 
    "src/xercesc/framework/psvi/PSVIElement.cpp" 
    "src/xercesc/framework/psvi/PSVIItem.cpp" 
    "src/xercesc/framework/psvi/XSAnnotation.cpp" 
    "src/xercesc/framework/psvi/XSAttributeDeclaration.cpp" 
    "src/xercesc/framework/psvi/XSAttributeGroupDefinition.cpp" 
    "src/xercesc/framework/psvi/XSAttributeUse.cpp" 
    "src/xercesc/framework/psvi/XSComplexTypeDefinition.cpp" 
    "src/xercesc/framework/psvi/XSElementDeclaration.cpp" 
    "src/xercesc/framework/psvi/XSFacet.cpp" 
    "src/xercesc/framework/psvi/XSIDCDefinition.cpp" 
    "src/xercesc/framework/psvi/XSModel.cpp" 
    "src/xercesc/framework/psvi/XSModelGroup.cpp" 
    "src/xercesc/framework/psvi/XSModelGroupDefinition.cpp" 
    "src/xercesc/framework/psvi/XSMultiValueFacet.cpp" 
    "src/xercesc/framework/psvi/XSNamespaceItem.cpp" 
    "src/xercesc/framework/psvi/XSNotationDeclaration.cpp" 
    "src/xercesc/framework/psvi/XSObject.cpp" 
    "src/xercesc/framework/psvi/XSParticle.cpp" 
    "src/xercesc/framework/psvi/XSSimpleTypeDefinition.cpp" 
    "src/xercesc/framework/psvi/XSTypeDefinition.cpp" 
    "src/xercesc/framework/psvi/XSValue.cpp" 
    "src/xercesc/framework/psvi/XSWildcard.cpp" 
    "src/xercesc/internal/BinFileOutputStream.cpp" 
    "src/xercesc/internal/BinMemOutputStream.cpp" 
    "src/xercesc/framework/BinOutputStream.cpp" 
    "src/xercesc/internal/DGXMLScanner.cpp" 
    "src/xercesc/internal/ElemStack.cpp" 
    "src/xercesc/internal/IGXMLScanner.cpp" 
    "src/xercesc/internal/IGXMLScanner2.cpp" 
    "src/xercesc/internal/MemoryManagerImpl.cpp" 
    "src/xercesc/internal/ReaderMgr.cpp" 
    "src/xercesc/internal/SGXMLScanner.cpp" 
    "src/xercesc/internal/ValidationContextImpl.cpp" 
    "src/xercesc/internal/VecAttributesImpl.cpp" 
    "src/xercesc/internal/VecAttrListImpl.cpp" 
    "src/xercesc/internal/WFXMLScanner.cpp" 
    "src/xercesc/internal/XMLReader.cpp" 
    "src/xercesc/internal/XMLScanner.cpp" 
    "src/xercesc/internal/XMLScannerResolver.cpp" 
    "src/xercesc/internal/XProtoType.cpp" 
    "src/xercesc/internal/XSAXMLScanner.cpp" 
    "src/xercesc/internal/XSerializeEngine.cpp" 
    "src/xercesc/internal/XSObjectFactory.cpp" 
    "src/xercesc/internal/XTemplateSerializer.cpp" 
    "src/xercesc/sax/Dummy.cpp" 
    "src/xercesc/sax/InputSource.cpp" 
    "src/xercesc/sax/SAXException.cpp" 
    "src/xercesc/sax/SAXParseException.cpp" 
    "src/xercesc/parsers/AbstractDOMParser.cpp" 
    "src/xercesc/parsers/DOMLSParserImpl.cpp" 
    "src/xercesc/parsers/SAX2XMLFilterImpl.cpp" 
    "src/xercesc/parsers/SAX2XMLReaderImpl.cpp" 
    "src/xercesc/parsers/SAXParser.cpp" 
    "src/xercesc/parsers/XercesDOMParser.cpp" 
    "src/xercesc/validators/common/AllContentModel.cpp" 
    "src/xercesc/validators/common/CMAny.cpp" 
    "src/xercesc/validators/common/CMBinaryOp.cpp" 
    "src/xercesc/validators/common/CMUnaryOp.cpp" 
    "src/xercesc/validators/common/ContentLeafNameTypeVector.cpp" 
    "src/xercesc/validators/common/ContentSpecNode.cpp" 
    "src/xercesc/validators/common/DFAContentModel.cpp" 
    "src/xercesc/validators/common/Grammar.cpp" 
    "src/xercesc/validators/common/GrammarResolver.cpp" 
    "src/xercesc/validators/common/MixedContentModel.cpp" 
    "src/xercesc/validators/common/SimpleContentModel.cpp" 
    "src/xercesc/validators/datatype/AbstractNumericFacetValidator.cpp" 
    "src/xercesc/validators/datatype/AbstractNumericValidator.cpp" 
    "src/xercesc/validators/datatype/AbstractStringValidator.cpp" 
    "src/xercesc/validators/datatype/AnySimpleTypeDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/AnyURIDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/Base64BinaryDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/BooleanDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DatatypeValidatorFactory.cpp" 
    "src/xercesc/validators/datatype/DateDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DateTimeDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DateTimeValidator.cpp" 
    "src/xercesc/validators/datatype/DayDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DecimalDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DoubleDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/DurationDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/ENTITYDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/FloatDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/HexBinaryDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/IDDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/IDREFDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/ListDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/MonthDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/MonthDayDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/NameDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/NCNameDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/NOTATIONDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/QNameDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/StringDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/TimeDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/UnionDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/XMLCanRepGroup.cpp" 
    "src/xercesc/validators/datatype/YearDatatypeValidator.cpp" 
    "src/xercesc/validators/datatype/YearMonthDatatypeValidator.cpp" 
    "src/xercesc/validators/DTD/DTDAttDef.cpp" 
    "src/xercesc/validators/DTD/DTDAttDefList.cpp" 
    "src/xercesc/validators/DTD/DTDElementDecl.cpp" 
    "src/xercesc/validators/DTD/DTDEntityDecl.cpp" 
    "src/xercesc/validators/DTD/DTDGrammar.cpp" 
    "src/xercesc/validators/DTD/DTDScanner.cpp" 
    "src/xercesc/validators/DTD/DTDValidator.cpp" 
    "src/xercesc/validators/DTD/XMLDTDDescriptionImpl.cpp" 
    "src/xercesc/validators/schema/ComplexTypeInfo.cpp" 
    "src/xercesc/validators/schema/GeneralAttributeCheck.cpp" 
    "src/xercesc/validators/schema/NamespaceScope.cpp" 
    "src/xercesc/validators/schema/SchemaAttDef.cpp" 
    "src/xercesc/validators/schema/SchemaAttDefList.cpp" 
    "src/xercesc/validators/schema/SchemaElementDecl.cpp" 
    "src/xercesc/validators/schema/SchemaGrammar.cpp" 
    "src/xercesc/validators/schema/SchemaInfo.cpp" 
    "src/xercesc/validators/schema/SchemaSymbols.cpp" 
    "src/xercesc/validators/schema/SchemaValidator.cpp" 
    "src/xercesc/validators/schema/SubstitutionGroupComparator.cpp" 
    "src/xercesc/validators/schema/TraverseSchema.cpp" 
    "src/xercesc/validators/schema/XercesAttGroupInfo.cpp" 
    "src/xercesc/validators/schema/XercesElementWildcard.cpp" 
    "src/xercesc/validators/schema/XercesGroupInfo.cpp" 
    "src/xercesc/validators/schema/XMLSchemaDescriptionImpl.cpp" 
    "src/xercesc/validators/schema/XSDDOMParser.cpp" 
    "src/xercesc/validators/schema/XSDErrorReporter.cpp" 
    "src/xercesc/validators/schema/XSDLocator.cpp" 
    "src/xercesc/validators/schema/XUtil.cpp" 
    "src/xercesc/validators/schema/identity/FieldActivator.cpp" 
    "src/xercesc/validators/schema/identity/FieldValueMap.cpp" 
    "src/xercesc/validators/schema/identity/IC_Field.cpp" 
    "src/xercesc/validators/schema/identity/IC_Key.cpp" 
    "src/xercesc/validators/schema/identity/IC_KeyRef.cpp" 
    "src/xercesc/validators/schema/identity/IC_Selector.cpp" 
    "src/xercesc/validators/schema/identity/IC_Unique.cpp" 
    "src/xercesc/validators/schema/identity/IdentityConstraint.cpp" 
    "src/xercesc/validators/schema/identity/IdentityConstraintHandler.cpp" 
    "src/xercesc/validators/schema/identity/ValueStore.cpp" 
    "src/xercesc/validators/schema/identity/ValueStoreCache.cpp" 
    "src/xercesc/validators/schema/identity/XercesXPath.cpp" 
    "src/xercesc/validators/schema/identity/XPathMatcher.cpp" 
    "src/xercesc/validators/schema/identity/XPathMatcherStack.cpp" 
    "src/xercesc/validators/schema/identity/XPathSymbols.cpp" 
    "src/xercesc/sax2/sax2Dummy.cpp" 
    "src/xercesc/dom/DOMException.cpp" 
    "src/xercesc/dom/DOMLSException.cpp" 
    "src/xercesc/dom/DOMRangeException.cpp" 
    "src/xercesc/dom/DOMXPathException.cpp" 
    "src/xercesc/dom/impl/DOMAttrImpl.cpp" 
    "src/xercesc/dom/impl/DOMAttrMapImpl.cpp" 
    "src/xercesc/dom/impl/DOMAttrNSImpl.cpp" 
    "src/xercesc/dom/impl/DOMCDATASectionImpl.cpp" 
    "src/xercesc/dom/impl/DOMCharacterDataImpl.cpp" 
    "src/xercesc/dom/impl/DOMChildNode.cpp" 
    "src/xercesc/dom/impl/DOMCommentImpl.cpp" 
    "src/xercesc/dom/impl/DOMConfigurationImpl.cpp" 
    "src/xercesc/dom/impl/DOMDeepNodeListImpl.cpp" 
    "src/xercesc/dom/impl/DOMDocumentFragmentImpl.cpp" 
    "src/xercesc/dom/impl/DOMDocumentImpl.cpp" 
    "src/xercesc/dom/impl/DOMDocumentTypeImpl.cpp" 
    "src/xercesc/dom/impl/DOMElementImpl.cpp" 
    "src/xercesc/dom/impl/DOMElementNSImpl.cpp" 
    "src/xercesc/dom/impl/DOMEntityImpl.cpp" 
    "src/xercesc/dom/impl/DOMEntityReferenceImpl.cpp" 
    "src/xercesc/dom/impl/DOMErrorImpl.cpp" 
    "src/xercesc/dom/impl/DOMImplementationImpl.cpp" 
    "src/xercesc/dom/impl/DOMImplementationListImpl.cpp" 
    "src/xercesc/dom/impl/DOMImplementationRegistry.cpp" 
    "src/xercesc/dom/impl/DOMLocatorImpl.cpp" 
    "src/xercesc/dom/impl/DOMLSInputImpl.cpp" 
    "src/xercesc/dom/impl/DOMLSOutputImpl.cpp" 
    "src/xercesc/dom/impl/DOMLSSerializerImpl.cpp" 
    "src/xercesc/dom/impl/DOMNamedNodeMapImpl.cpp" 
    "src/xercesc/dom/impl/DOMNodeIDMap.cpp" 
    "src/xercesc/dom/impl/DOMNodeImpl.cpp" 
    "src/xercesc/dom/impl/DOMNodeIteratorImpl.cpp" 
    "src/xercesc/dom/impl/DOMNodeListImpl.cpp" 
    "src/xercesc/dom/impl/DOMNodeVector.cpp" 
    "src/xercesc/dom/impl/DOMNormalizer.cpp" 
    "src/xercesc/dom/impl/DOMNotationImpl.cpp" 
    "src/xercesc/dom/impl/DOMParentNode.cpp" 
    "src/xercesc/dom/impl/DOMProcessingInstructionImpl.cpp" 
    "src/xercesc/dom/impl/DOMRangeImpl.cpp" 
    "src/xercesc/dom/impl/DOMStringListImpl.cpp" 
    "src/xercesc/dom/impl/DOMStringPool.cpp" 
    "src/xercesc/dom/impl/DOMTextImpl.cpp" 
    "src/xercesc/dom/impl/DOMTreeWalkerImpl.cpp" 
    "src/xercesc/dom/impl/DOMTypeInfoImpl.cpp" 
    "src/xercesc/dom/impl/DOMXPathExpressionImpl.cpp" 
    "src/xercesc/dom/impl/DOMXPathNSResolverImpl.cpp" 
    "src/xercesc/dom/impl/DOMXPathResultImpl.cpp" 
    "src/xercesc/dom/impl/XSDElementNSImpl.cpp" 
    "src/xercesc/xinclude/XIncludeDOMDocumentProcessor.cpp" 
    "src/xercesc/xinclude/XIncludeLocation.cpp" 
    "src/xercesc/xinclude/XIncludeUtils.cpp" 
)

include_directories(
src
src/xercesc/xinclude/
src/xercesc/dom/impl/
src/xercesc/dom/
src/xercesc/validators/schema/identity/
src/xercesc/validators/DTD/
src/xercesc/validators/datatype/
src/xercesc/validators/common/
src/xercesc/parsers/
src/xercesc/sax/
src/xercesc/internal/
src/xercesc/framework/psvi/
src/xercesc/framework/
src/xercesc/util/Transcoders/Win32/
src/xercesc/util/MsgLoaders/Win32/
src/xercesc/util/
src/xercesc/util/MutexManagers/
src/xercesc/util/FileManagers/
src/xercesc/util/regx/
src/xercesc/util/NetAccessors/WinSock/
src/xercesc/util/NetAccessors/
)

if (WIN32)
add_definitions(
	-DWIN32 
	-D_WINDOWS
	-D_CRT_SECURE_NO_DEPRECATE;
	-DXERCES_BUILDING_LIBRARY
	-DXERCES_USE_TRANSCODER_WINDOWS
	-DXERCES_USE_WIN32_MSGLOADER
	-DXERCES_USE_NETACCESSOR_WINSOCK
	-DXERCES_USE_FILEMGR_WINDOWS
	-DXERCES_USE_MUTEXMGR_WINDOWS
	-DXERCES_PATH_DELIMITER_BACKSLASH
	-DHAVE_STRICMP
	-DHAVE_STRNICMP
	-DHAVE_LIMITS_H
	-DHAVE_SYS_TIMEB_H
	-DHAVE_FTIME
	-DHAVE_WCSUPR
	-DHAVE_WCSLWR
	-DHAVE_WCSICMP
	-DHAVE_WCSNICMP
	)
else ()
add_definitions(
-DHAVE_STRICMP
	-DHAVE_STRNICMP
	-DHAVE_LIMITS_H
	-DHAVE_SYS_TIMEB_H
	-DHAVE_FTIME
	
)
endif()

	
add_library (xerces-c_3 ${XERCES_SOURCE} )
target_link_libraries (xerces-c_3 ws2_32.lib )

INSTALL(TARGETS xerces-c_3
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
  )

install(DIRECTORY 
	"src/xercesc"
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp" PATTERN "*.c")
	
endif()
