#include "SpatialVector.h"
#include "SpatialIndex.h"
#include "SpatialInterface.h"
#include "RangeConvex.h"
#include "HtmRange.h"
#include "HtmRangeIterator.h"
#include "VarStr.h"


int main(int argc, char *argv[]) {       
    int args = 1;
    bool quiet = false;
    size_t level;    
    size_t savelevel=10;
    
    while(args < argc) {      
        if  (strcmp(argv[args], "--quiet")==0) quiet = true;          
        else  {
            level = atoi(argv[args]);  
            break;
        }                 
        args++;           
    }
    
    SpatialVector* cnrs[4];
    float64 lat;
    float64 lon;
    args++;           
    if (args<argc-4){        
        // Get corners from arguments
        for (int c = 0 ; c < 4 ; c++ ) {      
            lat = atof(argv[args]);
            lon = atof(argv[args+1]);
            cnrs[c] = new SpatialVector();       
            cnrs[c]->setLatLonDegrees(lat, lon);                     
            args += 2;            
        }
    }
    else {
        // Get the corners from stdin
        for (int c = 0 ; c < 4 ; c++ ) {      
            if (!quiet) cout << "enter corner " << c << endl;
            cin >> lat;
            cin >> lon;
            cnrs[c] = new SpatialVector();         
            cnrs[c]->setLatLonDegrees(lat, lon);         
        }           
    }

    cout << 20 << endl << flush;
              
    SpatialIndex* si; 
    RangeConvex* conv;
    HtmRange htmRange;    
    char* symbol;
    
    cout << 30 << endl << flush;

    // create htm interface
    htmInterface htm(level,savelevel);

    cout << 40 << endl << flush;
  
    // Create spatial index at according level
    //si = new SpatialIndex(level,savelevel);    
    const SpatialIndex &index = htm.index();
    
    cout << 50 << endl << flush;

    // create spatial domain
    SpatialDomain domain(&index);   // initialize empty domain

    cout << 60 << endl << flush;
  
    // Create convex to represent the geometry
    conv = new RangeConvex(cnrs[0],cnrs[1],cnrs[2],cnrs[3]);

    cout << 70 << endl << flush;
    
    // Add convex to domain
    domain.add(*conv);

    cout << 80 << endl << flush;
        
    // Purge HTMRange
    htmRange.purge();

    cout << 90 << endl << flush;
        
    // Do the intersect. The boolean is for varlength ids or not
    //conv->intersect(si,htmRange,false);
    domain.intersect(&index, &htmRange, false);	  // intersect with range
  
    cout << 100 << endl << flush;

    // Iterate through the indeces
    HtmRangeIterator iter(&htmRange);        
    char buffer[80];
    while (iter.hasNext()) {                
        //id = iter->next() ;
        symbol = iter.nextSymbolic(buffer);
        if (strlen(symbol)==level+2){
            cout << symbol << endl;
          }
    }
    //htmRange.print(HtmRange::LOWS, cout, true);
    cout << "done" << endl;            
    
}





