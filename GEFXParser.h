//
//  GEFXParser.h
//  snap-examples
//
//  Created by alexis matuk on 10/28/15.
//  Copyright (c) 2015 infolab. All rights reserved.
//

#ifndef snap_examples_GEFXParser_h
#define snap_examples_GEFXParser_h
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
typedef TUNGraph::TNodeI SnapNode;
typedef TUNGraph::TEdgeI SnapEdge;
class GEFXParser{
    std::ofstream file;
    std::string header;
    std::string nodeKeyConfig;
    bool directed;
public:
    GEFXParser(std::string fileName)
    {
        directed = false;
        std::string f = fileName+".gexf";
        const char * c = f.c_str();
        file.open(c, std::ofstream::out);
        header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
        file << header;
    }
    ~GEFXParser()
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
            std::string graphTag = "    <graph mode=\"static\" defaultedgetype=\""+_type+"\">\n";
            file << graphTag;
        }
    }
    void initNodes()
    {
        std::string initNode = "        <nodes>\n";
        if(file.is_open())
            file << initNode;
    }
    void closeNodes()
    {
        std::string closeNode = "        </nodes>\n";
        if(file.is_open())
            file << closeNode;
    }
    void initEdges()
    {
        std::string initEdge = "        <edges>\n";
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
        std::string   initNode = "            <node id=\""+id+"\" label=\""+id+"\"/>\n";
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
        
        std::string initEdge = "            <edge source=\""+src+"\" target=\""+dest+"\"/>\n";
        if(file.is_open())
            file << initEdge;
    }
    void endGraph()
    {
        if(file.is_open())
            file << "    </graph>\n</gexf>";
    }
};

#endif
