var r0, r1, rands, off, num_imgs, pairs;

function setup() {
  var w = 600;
  var h = 600;
  createCanvas(w, h);
  background(0);
  stroke(100);
  noSmooth();

  num_imgs_in_row = 80;
  num_all_tiles = num_imgs_in_row * num_imgs_in_row;
  off = w / num_imgs_in_row;
  pairs = Array(num_all_tiles).fill()
  
  for(var i=0; i<num_all_tiles; i++) {
    if(i==0) { 
      pairs[i] = [random(off), random(off)];
    } else {
      pairs[i] = [pairs[i-1][1], random(off)];
    }
  }

  r0 = random(off);
  r1 = random(off);
  rands = [r0, r1];
}

function draw() {
  for (var i = 0; i < num_imgs_in_row; i++) {
    for (var j = 0; j < num_imgs_in_row; j++) {
      var idx = j*num_imgs_in_row + i;
      line(i*off, j*off+pairs[idx][0], i*off+off, j*off+pairs[idx][1]);
    }
  }
  noLoop();
}