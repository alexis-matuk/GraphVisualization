//
//  GraphSONParser.h
//  snap-examples
//
//  Created by alexis matuk on 10/28/15.
//  Copyright (c) 2015 infolab. All rights reserved.
//

#ifndef snap_examples_GraphSONParser_h
#define snap_examples_GraphSONParser_h

#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
typedef TUNGraph::TNodeI SnapNode;
typedef TUNGraph::TEdgeI SnapEdge;
class GraphSONParser{
    std::ofstream file;
    std::string header;
    std::string nodeKeyConfig;
    bool directed;
public:
    GraphSONParser(std::string fileName)
    {
        directed = false;
        std::string f = fileName+".graphson";
        const char * c = f.c_str();
        file.open(c, std::ofstream::out);
        file << "{\n";
    }
    ~GraphSONParser()
    {
        if(file.is_open())
            file.close();
    }
    void initGraph()
    {
        std::string initGraph = "    \"graph\": {\n";
        std::string initMode = "        \"mode\":\"NORMAL\",\n";
        if(file.is_open())
            file << initGraph << initMode;
    }
    void endGraph()
    {
        std::string closeGraph = "    }\n}\n";
        if(file.is_open())
            file << closeGraph;
    }
    void initNodes()
    {
        std::string initNode = "        \"vertices\": [\n";
        if(file.is_open())
            file << initNode;
    }
    void closeNodes()
    {
        std::string closeNode = "        ],\n";
        if(file.is_open())
            file << closeNode;
    }
    void initEdges()
    {
        std::string initEdge = "        \"edges\": [\n";
        if(file.is_open())
            file << initEdge;
    }
    void closeEdges()
    {
        std::string closeEdge = "        ]\n";
        if(file.is_open())
            file << closeEdge;
    }
    void writeNode(SnapNode & node, bool last)
    {
        int Number = node.GetId();
        std::ostringstream stream;
        stream << Number;
        std::string id = static_cast<std::ostringstream*>( &stream )->str();
        std::string initNode = "";
        if(last)
        {
            std::string indent = "            ";
            initNode = indent +"{\n"+indent+"    \"_id\": "+'"'+id+'"'+",\n"+indent+"    \"_type\": \"vertex\"\n"+indent+"}\n";
        }
        else
        {
            std::string indent = "            ";
            initNode = indent +"{\n"+indent+"    \"_id\": "+'"'+id+'"'+",\n"+indent+"    \"_type\": \"vertex\"\n"+indent+"},"+'\n';
            
        }
        if(file.is_open())
            file << initNode;
    }
    void writeEdge(SnapEdge & edge, bool last)
    {
        int edgeId = edge.GetId();
        int edgeSource = edge.GetSrcNId();
        int edgeDest = edge.GetDstNId();
        std::ostringstream stream1, stream2, stream3;
        stream1 << edgeId;
        stream2 << edgeSource;
        stream3 << edgeDest;
        std::string id = static_cast<std::ostringstream*>( &stream1)->str();
        std::string src = static_cast<std::ostringstream*>( &stream2 )->str();
        std::string dest = static_cast<std::ostringstream*>( &stream3 )->str();
        std::string initEdge = "";
        if(last)
        {
            std::string indent = "            ";
            initEdge = indent+"{\n"+indent+"    \"_type\": \"edge\",\n"+indent+"    \"_outV\": "+'"'+src+'"'+",\n"+indent+"    \"_inV\": "+'"'+dest+'"'+"\n"+indent+"}\n";
        }
        else
        {
            std::string indent = "            ";
            initEdge = indent+"{\n"+indent+"    \"_type\": \"edge\",\n"+indent+"    \"_outV\": "+'"'+src+'"'+",\n"+indent+"    \"_inV\": "+'"'+dest+'"'+"\n"+indent+"},\n";
            
        }
        if(file.is_open())
            file << initEdge;
    }
};

#endif
