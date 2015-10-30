
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
#include <iostream>
#include "stdafx.h"
#include "GEFXParser.h"
#include "GraphMLParser.h"
#include "GDFParser.h"
#include "GraphSONParser.h"

int main(int argc, char* argv[]) {
    
    std::cout << "Exporting to GraphML..." << std::endl;
    PUNGraph Graph = TUNGraph::New();
    Graph = TSnap::LoadEdgeList<PUNGraph>("p2p-Gnutella08.txt",0,1);
    GraphMLParser graphMl("CollabRelativityGraphMl");
    graphMl.initializeGraph("directed");
    for(SnapNode NI = Graph->BegNI(); NI!=Graph->EndNI(); NI++)
        graphMl.writeNode(NI);
    for(SnapEdge EI = Graph->BegEI(); EI!=Graph->EndEI(); EI++)
        graphMl.writeEdge(EI);
    graphMl.endGraph();
    std::cout << "File: CollabRelativityGSON.graphml created in ./ directory" << std::endl;
    std::cout << "Finished exporting to GraphML" << std::endl;
    
    
    std::cout << "Exporting to GEXF..." << std::endl;
    GEFXParser gfx("CollabRelativityGEXF");
    gfx.initializeGraph("directed");
    gfx.initNodes();
    for(SnapNode NI = Graph->BegNI(); NI!=Graph->EndNI(); NI++)
        gfx.writeNode(NI);
    gfx.closeNodes();
    gfx.initEdges();
    for(SnapEdge EI = Graph->BegEI(); EI!=Graph->EndEI(); EI++)
        gfx.writeEdge(EI);
    gfx.closeEdges();
    gfx.endGraph();
    std::cout << "File: CollabRelativityGSON.gexf created in ./ directory" << std::endl;
    std::cout << "Finished exporting to GEXF" << std::endl;
    
    std::cout << "Exporting to GDF..." << std::endl;
    GDFParser gdf("CollabRelativityGDF");
    gdf.initNodes();
    for(SnapNode NI = Graph->BegNI(); NI!=Graph->EndNI(); NI++)
        gdf.writeNode(NI);
    gdf.initEdges();
    for(SnapEdge EI = Graph->BegEI(); EI!=Graph->EndEI(); EI++)
        gdf.writeEdge(EI);
    std::cout << "File: CollabRelativityGSON.gdf created in ./ directory" << std::endl;
    std::cout << "Finished exporting to GDF" << std::endl;
    
    std::cout << "Exporting to GraphSON..." << std::endl;
    GraphSONParser gson("CollabRelativityGSON");
    int nodeCounter = 0;
    int edgeCounter = 0;
    gson.initGraph();
    gson.initNodes();
    for(SnapNode NI = Graph->BegNI(); NI!=Graph->EndNI(); NI++)
    {
        nodeCounter++;
        if(nodeCounter == Graph->GetNodes())
            gson.writeNode(NI, true);
        else
            gson.writeNode(NI, false);
    }
    gson.closeNodes();
    gson.initEdges();
    for(SnapEdge EI = Graph->BegEI(); EI!=Graph->EndEI(); EI++)
    {
        edgeCounter++;
        if(edgeCounter == Graph->GetEdges())
            gson.writeEdge(EI, true);
        else
            gson.writeEdge(EI, false);
    }
    gson.closeEdges();
    gson.endGraph();
    std::cout << "File: CollabRelativityGSON.graphson created in ./ directory" << std::endl;
    std::cout << "Finished exporting to GraphSON" << std::endl;
    
}
