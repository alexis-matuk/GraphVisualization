//
//  GDFParser.h
//  snap-examples
//
//  Created by alexis matuk on 10/28/15.
//  Copyright (c) 2015 infolab. All rights reserved.
//

#ifndef snap_examples_GDFParser_h
#define snap_examples_GDFParser_h
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
typedef TUNGraph::TNodeI SnapNode;
typedef TUNGraph::TEdgeI SnapEdge;
class GDFParser{
    std::ofstream file;
    std::string header;
    std::string nodeKeyConfig;
    bool directed;
public:
    GDFParser(std::string fileName)
    {
        directed = false;
        std::string f = fileName+".gdf";
        const char * c = f.c_str();
        file.open(c, std::ofstream::out);
    }
    ~GDFParser()
    {
        if(file.is_open())
            file.close();
    }
    void initNodes()
    {
        std::string initNode = "nodedef>name VARCHAR\n";
        if(file.is_open())
            file << initNode;
    }
    void initEdges()
    {
        std::string initEdge = "edgedef>node1 VARCHAR,node2 VARCHAR\n";
        if(file.is_open())
            file << initEdge;
    }
    void closeEdges()
    {
        std::string closeEdge = "        </edges>\n";
        if(file.is_open())
            file << closeEdge;
    }
    void writeNode(SnapNode & node)
    {
        int Number = node.GetId();
        std::ostringstream stream;
        stream << Number;
        std::string id = static_cast<std::ostringstream*>( &stream )->str();
        std::string initNode = id+"\n";
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
        std::string initEdge = src+","+dest+"\n";
        if(file.is_open())
            file << initEdge;
    }
};

#endif
