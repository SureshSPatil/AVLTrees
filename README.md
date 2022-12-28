# AVLTrees
To run:  
make avl  
./avl  

#Exmaple Run
Original BT:
BT Depth:4
                             ROOT                              
                               |                               
                               |                               
                               4                               
                              / \                              
                             /   \                             
                            /     \                            
                           /       \                           
                          /         \                          
                         /           \                         
                        /             \                        
                       /               \                       
                      /                 \                      
                     /                   \                     
                    /                     \                    
                   /                       \                   
                  /                         \                  
                 /                           \                 
                /                             \                
               2                              10               
              /                               / \              
             /                               /   \             
            /                               /     \            
           /                               /       \           
          /                               /         \          
         /                               /           \         
        /                               /             \        
       1                               8              12       
      /                               / \               \      
     /                               /   \               \     
    /                               /     \               \    
   0                               5       9              13   
  /                                                         \  
-1                                                          27 

Balanced BT:
BT Depth:3
             ROOT              
               |               
               |               
               9               
              / \              
             /   \             
            /     \            
           /       \           
          /         \          
         /           \         
        /             \        
       1              12       
      / \             / \      
     /   \           /   \     
    /     \         /     \    
   0       4      10      13   
  /       / \               \  
-1       2   8   
