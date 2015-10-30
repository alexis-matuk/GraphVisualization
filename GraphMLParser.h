//
//  GraphMLParser.h
//  snap-examples
//
//  Created by alexis matuk on 10/28/15.
//  Copyright (c) 2015 infolab. All rights reserved.
//

#ifndef snap_examples_GraphMLParser_h
#define snap_examples_GraphMLParser_h
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
typedef TUNGraph::TNodeI SnapNode;
typedef TUNGraph::TEdgeI SnapEdge;

class GraphMLParser{
    std::ofstream file;
    std::string header;
    std::string nodeKeyConfig;
    bool directed;
public:
    GraphMLParser(std::string fileName)
    {
        directed = false;
        std::string f = fileName+".graphml";
        const char * c = f.c_str();
        file.open(c, std::ofstream::out);
        header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
        nodeKeyConfig = "<key id=\"d0\" for=\"node\" attr.name=\"color\" attr.type=\"string\">\n    <default>yellow</default>\n</key>\n<key id=\"d1\" for=\"edge\" attr.name=\"weight\" attr.type=\"double\"/>\n";
        file << header;
        file << nodeKeyConfig;
    }
    ~GraphMLParser()
    {
        if(file.is_open())
            file.close();
    }
    void initializeGraph(std::string _type)
    {
        if(file.is_open())
        {
            if(_type == "undirected")
                directed = false;
            else
                directed = true;
            std::string graphTag = "   <graph id=\"G\" edgedefault=\""+_type+"\">\n";
            file << graphTag;
        }
    }
    void writeNode(SnapNode & node)
    {
        int Number = node.GetId();
        std::ostringstream stream;
        stream << Number;
        std::string id = static_cast<std::ostringstream*>( &stream )->str();
        std::string initNode = "        <node id=\""+id+"\"/>\n";
        if(file.is_open())
            file << initNode;
    }
    void writeEdge(SnapEdge & edge)
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
        if(directed)
        {
            std::string initEdge = "        <edge directed = \"true\" source=\""+src+"\" target=\""+dest+"\"/>\n";
            if(file.is_open())
                file << initEdge;
        }
        else
        {
            std::string initEdge = "        <edge source=\""+src+"\" target=\""+dest+"\"/>\n";
            if(file.is_open())
                file << initEdge;
        }
    }
    void endGraph()
    {
        if(file.is_open())
            file << "    </graph>\n</graphml>";
    }
};

#endif
