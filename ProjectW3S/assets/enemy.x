xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
       0.113750, 0.000000, 0.000000, 0.000000,
       0.000000, 0.113750, 0.000000, 0.000000,
       0.000000, 0.000000, 0.113750, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      8;
       1.000000; 1.000000; 1.000000;,
       1.000000; 1.000000;-1.000000;,
       1.000000;-1.000000; 1.000000;,
       1.000000;-1.000000;-1.000000;,
      -1.000000; 1.000000; 1.000000;,
      -1.000000; 1.000000;-1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000;-1.000000;-1.000000;;
      6;
      4;2,6,4,0;,
      4;7,3,1,5;,
      4;7,6,2,3;,
      4;3,2,0,1;,
      4;1,0,4,5;,
      4;5,4,6,7;;
      MeshNormals { // Cube normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
        -1.000000;-0.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube normals
      MeshMaterialList { // Cube material list
        2;
        6;
        1,
        1,
        1,
        1,
        1,
        1;
        Material Material_001 {
           1.000000; 0.297539; 0.014636; 1.000000;;
           96.078431;
           0.526316; 0.526316; 0.526316;;
           0.000000; 0.000000; 0.000000;;
        }
        Material Material {
           0.800000; 0.063461; 0.029148; 1.000000;;
           96.078431;
           1.000000; 1.000000; 1.000000;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
  Frame Cube_001 {
    FrameTransformMatrix {
       0.162500, 0.000000, 0.000000, 0.000000,
       0.000000, 0.162500, 0.000000, 0.000000,
       0.000000, 0.000000, 0.162500, 0.000000,
       0.000000, 0.650000, 0.000000, 1.000000;;
    }
    Mesh { // Cube_001 mesh
      8;
       2.000000; 2.000000; 2.000000;,
       2.000000; 2.000000;-2.000000;,
       2.000000;-2.000000; 2.000000;,
       2.000000;-2.000000;-2.000000;,
      -2.000000; 2.000000; 2.000000;,
      -2.000000; 2.000000;-2.000000;,
      -2.000000;-2.000000; 2.000000;,
      -2.000000;-2.000000;-2.000000;;
      6;
      4;2,6,4,0;,
      4;7,3,1,5;,
      4;7,6,2,3;,
      4;3,2,0,1;,
      4;1,0,4,5;,
      4;5,4,6,7;;
      MeshNormals { // Cube_001 normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
        -1.000000;-0.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube_001 normals
      MeshMaterialList { // Cube_001 material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material_001 {
           1.000000; 0.297539; 0.014636; 1.000000;;
           96.078431;
           0.526316; 0.526316; 0.526316;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube_001 material list
    } // End of Cube_001 mesh
  } // End of Cube_001
  Frame Cube_002 {
    FrameTransformMatrix {
       0.162500, 0.000000, 0.000000, 0.000000,
       0.000000, 0.162500, 0.000000, 0.000000,
       0.000000, 0.000000, 0.162500, 0.000000,
      -0.650000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube_002 mesh
      8;
       2.000000; 2.000000; 2.000000;,
       2.000000; 2.000000;-2.000000;,
       2.000000;-2.000000; 2.000000;,
       2.000000;-2.000000;-2.000000;,
      -2.000000; 2.000000; 2.000000;,
      -2.000000; 2.000000;-2.000000;,
      -2.000000;-2.000000; 2.000000;,
      -2.000000;-2.000000;-2.000000;;
      6;
      4;2,6,4,0;,
      4;7,3,1,5;,
      4;7,6,2,3;,
      4;3,2,0,1;,
      4;1,0,4,5;,
      4;5,4,6,7;;
      MeshNormals { // Cube_002 normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
        -1.000000;-0.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube_002 normals
      MeshMaterialList { // Cube_002 material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material_001 {
           1.000000; 0.297539; 0.014636; 1.000000;;
           96.078431;
           0.526316; 0.526316; 0.526316;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube_002 material list
    } // End of Cube_002 mesh
  } // End of Cube_002
  Frame Cube_003 {
    FrameTransformMatrix {
       0.162500, 0.000000, 0.000000, 0.000000,
       0.000000, 0.162500, 0.000000, 0.000000,
       0.000000, 0.000000, 0.162500, 0.000000,
       0.650000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube_003 mesh
      8;
       2.000000; 2.000000; 2.000000;,
       2.000000; 2.000000;-2.000000;,
       2.000000;-2.000000; 2.000000;,
       2.000000;-2.000000;-2.000000;,
      -2.000000; 2.000000; 2.000000;,
      -2.000000; 2.000000;-2.000000;,
      -2.000000;-2.000000; 2.000000;,
      -2.000000;-2.000000;-2.000000;;
      6;
      4;2,6,4,0;,
      4;7,3,1,5;,
      4;7,6,2,3;,
      4;3,2,0,1;,
      4;1,0,4,5;,
      4;5,4,6,7;;
      MeshNormals { // Cube_003 normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
        -1.000000;-0.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube_003 normals
      MeshMaterialList { // Cube_003 material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material_001 {
           1.000000; 0.297539; 0.014636; 1.000000;;
           96.078431;
           0.526316; 0.526316; 0.526316;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube_003 material list
    } // End of Cube_003 mesh
  } // End of Cube_003
  Frame Cube_004 {
    FrameTransformMatrix {
       0.162500, 0.000000, 0.000000, 0.000000,
       0.000000, 0.162500, 0.000000, 0.000000,
       0.000000, 0.000000, 0.162500, 0.000000,
       0.000000,-0.650000, 0.000000, 1.000000;;
    }
    Mesh { // Cube_004 mesh
      8;
       2.000000; 2.000000; 2.000000;,
       2.000000; 2.000000;-2.000000;,
       2.000000;-2.000000; 2.000000;,
       2.000000;-2.000000;-2.000000;,
      -2.000000; 2.000000; 2.000000;,
      -2.000000; 2.000000;-2.000000;,
      -2.000000;-2.000000; 2.000000;,
      -2.000000;-2.000000;-2.000000;;
      6;
      4;2,6,4,0;,
      4;7,3,1,5;,
      4;7,6,2,3;,
      4;3,2,0,1;,
      4;1,0,4,5;,
      4;5,4,6,7;;
      MeshNormals { // Cube_004 normals
        6;
         0.000000;-0.000000; 1.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
        -1.000000;-0.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube_004 normals
      MeshMaterialList { // Cube_004 material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material_001 {
           1.000000; 0.297539; 0.014636; 1.000000;;
           96.078431;
           0.526316; 0.526316; 0.526316;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube_004 material list
    } // End of Cube_004 mesh
  } // End of Cube_004
} // End of Root
