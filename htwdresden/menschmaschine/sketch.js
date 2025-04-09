let player;
let platforms = [];
let coin;
let smallCoins = [];
let score = 0;
let bgImage;
let playerIMG;
let music;

let video;
let handposeModel;
let predictions = [];

let speech = new p5.SpeechRec('en-US');

let gameState = 'menu';
let selectedLevel = 0; // 0 = leicht, 1 = mittel, 2 = schwer
let levelLayouts = [[], [], []]; // Plattform-Layouts für die Level

//////////////////////////////////////////////////////////////////////
function preLoad() {
  

}

//////////////////////////////////////////////////////////////////////
function setup() {
  new Canvas(windowWidth, windowHeight, "pixelated");

  //bgImage = loadImage('assets/lost_kingdom.png');
  playerIMG = loadImage('assets/player-1.png');
  music = loadSound('assets/tune.mp3');
  coinSound = loadSound('assets/coin.mp3');
  failSound = loadSound('assets/fail.mp3');
  winSound = loadSound('assets/win.mp3');
        
  player = new Sprite;
  //player.image = 'assets/player-1.png';
  player.addAni('assets/player_walk1.png', 4);
  player.rotationLock = true;
  //player.debug = true;
  player.h = 75;
        
  video = createCapture(VIDEO);
  video.size(300, 200);
  video.hide();

  handpose.load().then(model => {
    handposeModel = model;
    console.log("Handpose model loaded!");
  }).catch(err => {
    console.error("Error loading Handpose model:", err);
  });

  let continuous = true;
  let interim = true;  
  speech.onResult = handleSpeech;
  speech.start(continuous, interim);

  speech.onEnd = () => {
    console.log("Speech recognition restarted.");
    speech.start(); // Startet die Spracherkennung erneut
  };

  allSprites.autoDraw = false;
  allSprites.autoUpdate = false;
  world.autoStep = false;

  setupLevelLayouts();
}

//////////////////////////////////////////////////////////////////////
function draw() {
  
  if (gameState == 'menu') drawMenu();
  if (gameState == 'runGame') runGame();
  if (gameState === 'endScreen') drawEndScreen();
}

//////////////////////////////////////////////////////////////////////
async function detectHands() {
  if (!handposeModel) {
    console.warn('Handpose model is not loaded yet.');
    return;
  }

  const newPredictions = await handposeModel.estimateHands(video.elt);
  predictions = newPredictions; 

  if (predictions.length > 0) {
    let hand = predictions[0].landmarks;

    // X-Position des Zeigefingers verwenden
    let fingerX = hand[5][0];

    //Spieler basierend auf der Handposition bewegen
    if (fingerX > width / 4) {
      player.velocity.x = -5; // links
      player.scale.x = -1;
    } else if (fingerX < width / 2) {
      player.velocity.x = 5; // rechts
      player.scale.x = 1;
    } else {
      player.velocity.x = 0; // Stopp
      player.ani.pause();
    }
  } else {
    // Keine Hand erkannt, Bewegung stoppen
    player.velocity.x = 0;
  }
}

//////////////////////////////////////////////////////////////////////
let canJump = true;

function handleJump() {
  if (canJump && Math.abs(player.velocity.y) < 0.1) {
    player.velocity.y = -13;
    canJump = false;
    setTimeout(() => { canJump = true; }, 500); // 500ms Wartezeit
  }
}

function handleSpeech() {
  let action = speech.resultString.toLowerCase().trim();
  console.log('Command received:', speech.resultString);

  if (gameState === 'menu') {
    // Menüsteuerung
    if (action === 'easy') {
      selectedLevel = 0;
    } else if (action === 'medium') {
      selectedLevel = 1;
    } else if (action === 'hard') {
      selectedLevel = 2; 
    } else if (action === 'start') {
      loadLevel(selectedLevel); // Starte das ausgewählte Level
      //music.play();
      gameState = 'runGame'; // Wechsle zum Spielmodus
    }
  } else if (gameState === 'runGame') {
    // Spielfunktionen (z. B. Springen)
    if (action === 'jump') {
      handleJump();
    }
  }
}

function keyPressed() {
  if (gameState === 'menu') {
    if (keyCode === UP_ARROW) {
      selectedLevel = (selectedLevel - 1 + 3) % 3;
    } else if (keyCode === DOWN_ARROW) {
      selectedLevel = (selectedLevel + 1) % 3;
    } else if (keyCode === ENTER) {
      loadLevel(selectedLevel);;
      //music.play();
      gameState = 'runGame';
    }
  } else if (gameState === 'runGame') {
    if (key === 'w' || key === ' ') {
      handleJump();
    }
  } else if (gameState === 'endScreen') {
    if (keyCode === ENTER) {
      gameState = 'menu'; 
    } else if (key === 'r') {
      loadLevel(selectedLevel); 
      gameState = 'runGame';
    }
  }
}

//////////////////////////////////////////////////////////////////////
function drawMenu() {
  background('black');
  fill('gold');
  textAlign(CENTER, CENTER);
  textSize(70);
  text('HOLLOW STEPS', width / 2, height / 2 - 100);

  fill('white');
  textSize(20);
  text('Use voice commands or arrow keys to select difficulty', width / 2, height / 2 + 90);
  text('Say "start" or press ENTER to begin', width / 2, height / 2 + 120);

  const levels = ['Easy', 'Medium', 'Hard'];
  levels.forEach((level, index) => {
    fill(selectedLevel === index ? 'gold' : 'white');
    text(level, width / 2, height / 2 + 190 + index * 30);
  });

  image(playerIMG, width / 2 - 45, height / 2 - 20);
}

function drawEndScreen() {
  background('black');
  fill('gold');
  textAlign(CENTER, CENTER);
  textSize(70);
  text('Level Finished!', width / 2, height / 2 - 100);

  fill('white');
  textSize(20);
  text('Press ENTER to return to the menu', width / 2, height / 2 + 50);
  text('Press R to restart the level', width / 2, height / 2 + 100);
}

//////////////////////////////////////////////////////////////////////
function setupLevelLayouts() {
  levelLayouts[0] = [ // Leicht
    { x: 0, y: height - 20, w: 500, h: 20 },
    { x: width / 2 - 250, y: height - 20, w: 150, h: 20 },
    { x: width / 2 + 50, y: height - 20, w: 150, h: 20 },
    { x: width, y: height - 20, w: 900, h: 20 },

    { x: width / 2 + 600, y: 650, w: 200, h: 20 },
    { x: width / 2 + 50, y: 550, w: 500, h: 20 },
    { x: width / 2 - 450, y: 450, w: 200, h: 20 },

    { x: 0, y: 300, w: 200, h: 20 },
    { x: width / 2 - 300, y: 200, w: 200, h: 20 },
    { x: width / 2 + 100, y: 250, w: 200, h: 20 },
    { x: width / 2 + 500, y: 150, w: 300, h: 20 }
  ];
  levelLayouts[1] = [ // Mittel
    { x: width / 2, y: height - 20, w: width, h: 20 },
    { x: width / 2 - 150, y: 700, w: 200, h: 20 },
    { x: width / 2 + 115, y: 500, w: 150, h: 20 },
    { x: width / 2 - 250, y: 300, w: 150, h: 20 }
  ];
  levelLayouts[2] = [ // Schwer
    { x: width / 2, y: height - 20, w: width, h: 20 },
    { x: width / 2 - 250, y: 650, w: 150, h: 20 },
    { x: width / 2 + 200, y: 500, w: 150, h: 20 },
    { x: width / 2 - 300, y: 350, w: 120, h: 20 },
    { x: width / 2 + 250, y: 200, w: 120, h: 20 }
  ];
}


function loadLevel(levelIndex) {
  for (let platform of platforms) {
    platform.remove();
  }
  platforms = [];
  smallCoins = [];

  for (let layout of levelLayouts[levelIndex]) {
    let platform = new Sprite(layout.x, layout.y, layout.w, layout.h, 's');
    platform.color = 'DarkSlateGray';
    platform.collider = 'static';
    platform.scale.y = 1.1;
    platforms.push(platform);
  }

  coin = new Sprite(width / 2 + 500, 75);
  coin.addAni('assets/red_crystal_0000.png', 3);
  
  let smallCoinLayouts = [
    { x: width / 2 - 250, y: height - 75 },
    { x: width / 2 + 200, y: height - 200 },
    { x: width / 2 + 50, y: 400 },
    { x: 50, y: 250 },
    { x: width / 2 + 100, y: 200 }
  ];

  for (let layout of smallCoinLayouts) {
    let smallCoin = new Sprite(layout.x, layout.y);
    smallCoin.addAni('assets/green_crystal_0000.png', 3);
    smallCoin.scale = 0.75; // Kleinere Münze
    smallCoin.ani.frameDelay = 10;
    smallCoins.push(smallCoin);
  }

  score = 0;
  player.position = { x: 100, y: height - 100 };
}

//////////////////////////////////////////////////////////////////////
function runGame() {
  background('black');
  //image(bgImage, 0, 0);

  fill('white');
  textSize(20);
  text("Points: " + score, 60, 20);

  player.ani.play();
  player.ani.frameDelay = 10;
  coin.ani.play();
  coin.ani.frameDelay = 10;

  if (handposeModel) {
    detectHands();
  }

  let onPlatform = false;

  for (let platform of platforms) {
    if (
      player.collide(platform) && player.velocity.y >= 0) {
      onPlatform = true;
      player.velocity.y = 0;
      break;
    }
  }

  // Schwerkraft
  if (!onPlatform) {
    player.velocity.y += 0.5;
  }

  // Spieler darf nicht über Bildschirmrand laufen
  player.position.x = constrain(player.position.x, 0, width);

  // Überprüfen, ob der Spieler den unteren Bildschirmrand erreicht hat
  if (player.position.y > height + 50) {
    failSound.play();
    resetLevel(); // Level zurücksetzen
  }

  if (player.overlap(coin)) {
    score += 50;
    coin.remove();
    winSound.play();
    setTimeout(() => {
      gameState = 'endScreen'; // Wechsel zum Endbildschirm
    }, 500);
  }

  for (let i = smallCoins.length - 1; i >= 0; i--) {
    if (player.overlap(smallCoins[i])) {
      score += 10;
      smallCoins[i].remove();
      smallCoins.splice(i, 1);
      coinSound.play();
    }
  }

  allSprites.update();
  allSprites.draw();
  world.step();
}

//////////////////////////////////////////////////////////////////////
function resetLevel() {

  player.position = { x: 100, y: height - 100 };
  score = 0;

  // Entferne alle Münzen und erstelle sie neu
  for (let smallCoin of smallCoins) {
    smallCoin.remove();
  }
  smallCoins = [];

  coin.remove();
  loadLevel(selectedLevel);
}