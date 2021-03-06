/*
 * Fimex
 *
 * (C) Copyright 2009, met.no
 *
 * Project Info:  https://wiki.met.no/fimex/start
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include "testinghelpers.h"
#include "fimex/XMLDoc.h"
#include <libxml/tree.h>
#include <libxml/xpath.h>

using namespace std;
using namespace MetNoFimex;

TEST4FIMEX_TEST_CASE(test_xmlDoc)
{
    XMLDoc doc(pathTest("testXMLDoc.xml"));
    {
        xmlXPathObject_p xpathObj = doc.getXPathObject("/cdmQualityConfig");
        xmlNodeSetPtr nodes = xpathObj->nodesetval;
        int size = (nodes) ? nodes->nodeNr : 0;
        TEST4FIMEX_CHECK_EQ(size, 1);
        // check a subnode
        xpathObj = doc.getXPathObject("variable/status_flag_variable[@name=\"blub\"]", nodes->nodeTab[0]);
        xmlNodeSetPtr flagNodes = xpathObj->nodesetval;
        int flagNodesSize = (flagNodes) ? flagNodes->nodeNr : 0;
        TEST4FIMEX_CHECK(flagNodesSize >= 1);
        // check a subnode with full path
        xpathObj = doc.getXPathObject("/cdmQualityConfig/variable/status_flag_variable[@name=\"blub\"]");
        xmlNodeSetPtr flagNodes2 = xpathObj->nodesetval;
        int flagNodesSize2 = (flagNodes2) ? flagNodes2->nodeNr : 0;
        TEST4FIMEX_CHECK_EQ(flagNodesSize, flagNodesSize2);

        // check a subnode with full path
        xpathObj = doc.getXPathObject("/cdmQualityConfig/variable/status_flag_variable/allowed_values");
        std::string text = getXmlContent(xpathObj->nodesetval->nodeTab[0]);
        TEST4FIMEX_CHECK_EQ("1,2,...,6", text);

        string nodeDoc = doc.toString(xpathObj->nodesetval->nodeTab[0]);
        TEST4FIMEX_CHECK_EQ(nodeDoc, "<?xml version=\"1.0\"?>\n<allowed_values>1,2,...,6</allowed_values>\n");

        XMLDoc_p valueDoc = XMLDoc::fromString(nodeDoc, "");
        xpathObj = valueDoc->getXPathObject("/allowed_values");
        string values = getXmlContent(xpathObj->nodesetval->nodeTab[0]);
        TEST4FIMEX_CHECK_EQ("1,2,...,6", values);
    }
}
