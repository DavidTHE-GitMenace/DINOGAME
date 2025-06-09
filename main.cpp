#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp> // This is the graphics software used for the 2D game
#include <SFML/Audio.hpp> // Audio inclusion
using namespace sf;
#include <random>
#include <chrono>
#include <cstddef>
#include <string>

int main() {
    // Creating a Window
    RenderWindow dinoScreen(VideoMode(1600, 900), "Dino Window");

    // Colors that I need to custom make
    const Color red(255, 0, 0);
    const Color blue(0, 0, 255);
    const Color green(0, 255, 0);
    const Color purple(0, 255, 255);
    const Color lightGray(100, 100, 100);
    const Color gray(30, 30, 30);

    // Dark grey with 50% transparency (solid is 255, transparent is 0)
    sf::Color semiTransparentDarkGrey(90, 90, 90, 128);

    // DINO HITBOX: ---------------------------------
    RectangleShape dinoHead;
    dinoHead.setSize(Vector2f(53, 40));
    dinoHead.setFillColor(red);

    RectangleShape dinoBody1;
    dinoBody1.setSize(Vector2f(81, 36));
    dinoBody1.setFillColor(red);

    RectangleShape dinoBody2;
    dinoBody2.setSize(Vector2f(56, 12));
    dinoBody2.setFillColor(red);

    RectangleShape dinoBody3;
    dinoBody3.setSize(Vector2f(54, 12));
    dinoBody3.setFillColor(red);

    RectangleShape dinoBody4;
    dinoBody4.setSize(Vector2f(37, 22));
    dinoBody4.setFillColor(red);

    // ---------------------------------------------

    // PTERODACTYL HITBOX: -------------------------
    RectangleShape pterodactylHead;
    pterodactylHead.setSize(Vector2f(32, 30));
    pterodactylHead.setFillColor(red);

    RectangleShape pterodactylBody1;
    pterodactylBody1.setSize(Vector2f(70, 29));
    pterodactylBody1.setFillColor(blue);

    RectangleShape pterodactylBody2;
    pterodactylBody2.setSize(Vector2f(23, 53));
    pterodactylBody2.setFillColor(green);

    RectangleShape pterodactylUpperWing2;
    pterodactylUpperWing2.setSize(Vector2f(18, 36));
    pterodactylUpperWing2.setFillColor(blue);

    RectangleShape pterodactylUpperWing3;
    pterodactylUpperWing3.setSize(Vector2f(17, 20));
    pterodactylUpperWing3.setFillColor(red);

    
    // ---------------------------------------------

    RectangleShape dinoHitBoxLeft;
    dinoHitBoxLeft.setSize(Vector2f(2, 900));
    dinoHitBoxLeft.setPosition(0, 372);
    dinoHitBoxLeft.setFillColor(green);

    RectangleShape dinoHitBoxRight;
    dinoHitBoxRight.setSize(Vector2f(2, 900));
    dinoHitBoxRight.setPosition(0, 0);
    dinoHitBoxRight.setFillColor(purple);

    // -------------------------------------------

    // PTERODACTYL HITBOX: -----------------------------

    RectangleShape ptHitBoxRight;
    ptHitBoxRight.setFillColor(blue);

    RectangleShape ptHitBoxLeft;
    ptHitBoxLeft.setFillColor(blue);

    RectangleShape ptTop;
    ptTop.setFillColor(red);

    RectangleShape ptBottom;
    ptBottom.setFillColor(red);

    // -------------------------------------------


    // FONT FOR GAME TEXT: --------------------------------------------------

    Font pressStart;
    if (!pressStart.loadFromFile("gameTextFont/PressStart2P-Regular.ttf")) {
        cerr << "Failed to load font\n";
    }

    Text scoreText;
    scoreText.setFont(pressStart);                  // which font to use
    scoreText.setCharacterSize(35);                 // in pixels
    scoreText.setFillColor(lightGray);              // text color
    scoreText.setPosition(1560.f, 10.f);            // screen position

    Text zeros;
    zeros.setFont(pressStart);                      
    zeros.setCharacterSize(35);                     
    zeros.setFillColor(lightGray);                  
    zeros.setPosition(1560 - (4 * 35), 10.f);       

    Text zeross;
    zeross.setFont(pressStart);                      
    zeross.setCharacterSize(35);                     
    zeross.setFillColor(lightGray);                  
    zeross.setPosition(1560 - (10 * 35), 10.f);     
    
    Text High;
    High.setFont(pressStart);                      
    High.setCharacterSize(35);                     
    High.setFillColor(lightGray);                  
    High.setPosition(1560 - (13 * 35), 10.f);     
    
    Text HighScore;
    HighScore.setFont(pressStart);                      
    HighScore.setCharacterSize(35);                     
    HighScore.setFillColor(lightGray);                  
    HighScore.setPosition(1560 - (6 * 35), 10.f);     

    Text MetersModulusedby100;
    MetersModulusedby100.setFont(pressStart);                      
    MetersModulusedby100.setCharacterSize(35);                     
    MetersModulusedby100.setFillColor(lightGray);                  
    
    
    string highscore = "HI";
    string zeroString = "00000";
    string zeroString2 = "00000";
    
    zeros.setString(zeroString);
    zeross.setString(zeroString);
    High.setString(highscore);
    


    // ----------------------------------------------------------------------

    // JUMP MECHANICS: --------------------------------------------------------------------------------------------------------
    // Constants
    // His air-time needs to be around a bit over 0.5 seconds
    const float gravity = 980.0f; // Pixels per second squared
    const float jumpVelocity = -935.0f; // Initial upward velocity for the jump

    // Physics Variables we need
    float Y_Velocity = 0.0f; // Vertical velocity
    bool isJumping = false; // If dino is currently jumping in the air or not
    bool isDead = false;
    bool isDucking = false;
    bool isDeadSFXPlayed = false;
    bool is100MeterSFXPlayed = false;
    bool isScoreGone = false;
    bool every100Meters = false;
    float speed = -600.0f;

    // JUMP MECHANICS END HERE: -----------------------------------------------------------------------------------------------

    // Clock for timing 
    Clock clock;
    const float dinoFrameDuration = 0.1f;
    float ptFrameDuration = 0.5f;
    float distanceCalculation = 0.1f; 
    const float blinkingDuration = 0.25f;
    // int count = 0;

    // random variable for random spacing and random cactus sprites etc;
    mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(1670, 1790);
    int cactus1distance = dist(mt);
    uniform_int_distribution<int> dist2(2400, 2450);
    int cactus2distance = dist2(mt);
    uniform_int_distribution<int> cactiRandomizer(0, 5);
    int idx = cactiRandomizer(mt);
    int currentCactus = idx;
    uniform_int_distribution<int> groundRandomizer(0, 4);
    uniform_int_distribution<int> cloudYLevelRandomizer(100, 400);
    int cloudYLevel = cloudYLevelRandomizer(mt);
    uniform_int_distribution<int> cloudSpeedRandomizer(-600, -50);
    int cloudSpeed = cloudSpeedRandomizer(mt);
    uniform_real_distribution<float> cloudSizeRandomizer(1, 2.8);
    float cloudSize = cloudSizeRandomizer(mt);
    uniform_int_distribution<int> ptYLevelRandomizer(1, 3);
    int ptYLevel = ptYLevelRandomizer(mt);
    uniform_int_distribution<int> ptDistanceRandomizer(1670, 11500);
    int ptDistance = ptDistanceRandomizer(mt);
    uniform_int_distribution<int> spacingRandomizer(100, 500);
    int spacing = spacingRandomizer(mt);
    uniform_int_distribution<int> dayOrNightRandomizer(1, 2);
    int dayOrNight = dayOrNightRandomizer(mt);
    int distance = 0;
    int maxDistance = 0;
    int every100MetersMarked;

    scoreText.setString(to_string(distance));

    // SFX: -------------------------------------------------------------------------------------------------------------------

    SoundBuffer jumpSFX;
    if (!jumpSFX.loadFromFile("SoundEffects/jump.WAV")) {
        cerr << "Error: The jumping sound effect wasn't found." << endl;
        return -1;
    }

    SoundBuffer deathSFX;
    if (!deathSFX.loadFromFile("SoundEffects/death.WAV")) {
        cerr << "Error: The death sound effect wasn't found." << endl;
        return -1;
    }

    SoundBuffer meters_100SFX;
    if (!meters_100SFX.loadFromFile("SoundEffects/100Meters!.WAV")) {
        cerr << "Error: The death sound effect wasn't found." << endl;
        return -1;
    }

    Sound jump;
    jump.setBuffer(jumpSFX);

    Sound death;
    death.setBuffer(deathSFX);

    Sound meters_100;
    meters_100.setBuffer(meters_100SFX);

    // ------------------------------------------------------------------------------------------------------------------------

    // DINO SPRITE SHEET: -----------------------------------------------------------------------------------------------------
    Texture dinoFrameTexture;
    if (!dinoFrameTexture.loadFromFile("gameSheet.png")) {
        cerr << "Error: The image of the entire sprite sheet wasn't found for some reason." << endl;
        return -1;
    }

    Texture dinoDucking1;
    if (!dinoDucking1.loadFromFile("DinoFolder/dinoDucking1.png")) {
        cerr << "Error: The image of the first sprite of the dino ducking wasn't found for some reason." << endl;
        return -1;
    }

    Texture dinoDucking2;
    if (!dinoDucking2.loadFromFile("DinoFolder/dinoDucking2.png")) {
        cerr << "Error: The image of the second sprite of the dino ducking wasn't found for some reason." << endl;
        return -1;
    }

    // Making a sprite for the dino frames
    Sprite dinoFrameSprite;
    Sprite dinoDuckingFrameSprite;
    dinoFrameSprite.setTexture(dinoFrameTexture, true);

    const int dinoFrameWidth = 88;
    const int dinoFrameHeight = 110;
    const int dinoFrameXPosition = 1602;
    const int dinoFrameYPosition = -15; 

    dinoFrameSprite.setOrigin(0, 0);

    dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition, dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
    dinoFrameSprite.setPosition(40, 455);
    dinoFrameSprite.scale(1.2f, 1.2f);


    bool dinoRunningFrame1 = true; // tracks which frame is being currently displayed
    bool dinoDuckingFrame1 = true; 

    dinoDuckingFrameSprite.setTexture(dinoDucking1, true);
    dinoDuckingFrameSprite.scale(1.2f, 1.2f);
    auto duckBounds = dinoDuckingFrameSprite.getGlobalBounds();
    float duckH = duckBounds.height;

    auto dinoBounds = dinoFrameSprite.getGlobalBounds();
    const float groundCoord = dinoFrameSprite.getPosition().y + dinoBounds.height;

    // DINO SPRITE SHEET ENDS HERE: -------------------------------------------------------------------------------------------

    // PTERODACTYL SPRITE SHEET STARTS HERE: ----------------------------------------------------------------------------------
    Texture ptFlapDown;
    if (!ptFlapDown.loadFromFile("PterodactylFolder/pterodactylFlapDown.png")) {
        cerr << "Error: The image of the cloud wasn't found for some reason." << endl;
        return -1;
    }

    Texture ptFlapUp;
    if (!ptFlapUp.loadFromFile("PterodactylFolder/pterodactylFlapUp.png")) {
        cerr << "Error: The image of the cloud wasn't found for some reason." << endl;
        return -1;
    }

    Sprite pt;
    pt.setTexture(ptFlapDown, true);
    pt.scale(1.2f, 1.2f);
    pt.setPosition(3500, 440);

    bool ptFlap1 = true;
    auto ptBounds = pt.getGlobalBounds();
    // auto ptBounds2 = ptBounds;


    // PTERODACTYL SPRITE SHEET ENDS HERE: ------------------------------------------------------------------------------------

    // BACKGROUND SPRITES ARE HEREEEEE: ---------------------------------------------------------------------------------------
    Texture cloudTexture;
    if (!cloudTexture.loadFromFile("cloud.png")) {
        cerr << "Error: The image of the cloud wasn't found for some reason." << endl;
        return -1;
    }

    Sprite cloud;
    cloud.setTexture(cloudTexture, true);
    cloud.setPosition(cactus1distance + 100, cloudYLevel);
    cloud.setScale(cloudSize, cloudSize);

    Sprite cloud2;
    cloud2.setTexture(cloudTexture, true);
    cloud2.setPosition(cactus1distance + 100, cloudYLevel - 90);
    cloud2.setScale(cloudSize, cloudSize);


    Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("gameOver.png")) {
        cerr << "Error: The image of the game over text wasn't found for some reason." << endl;
        return -1;
    }

    Sprite gameOver;
    gameOver.setTexture(gameOverTexture, true);
    gameOver.setPosition(800, -200);
    gameOver.setScale(1.5f, 1.5f);


    Texture resetButtonTexture;
    if (!resetButtonTexture.loadFromFile("resetButton.png")) {
        cerr << "Error: The image of the game over text wasn't found for some reason." << endl;
        return -1;
    }

    Sprite resetButton;
    resetButton.setTexture(resetButtonTexture, true);
    resetButton.setPosition(800, -200);
    resetButton.setScale(1.5f, 1.5f);
    
    // BACKGROUND SPRITES END HERE: -------------------------------------------------------------------------------------------

    // CACTUS SPRITES ARE GOING TO BE HERE: -----------------------------------------------------------------------------------

    // Importing Single Cactus texture
    Texture singleCactusTexture;
    if (!singleCactusTexture.loadFromFile("CactiFolder/OneCactus.jpg")) {
        cerr << "Error: The one cactus file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Importing Single Small Cactus texture
    Texture singleSmallCactusTexture;
    if (!singleSmallCactusTexture.loadFromFile("CactiFolder/OneSmallCactus.png")) {
        cerr << "Error: The one SMALL cactus file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Importing Two Cacti texture
    Texture twoCactiTexture;
    if (!twoCactiTexture.loadFromFile("CactiFolder/twoCacti.png")) {
        cerr << "Error: The two cacti file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Importing Two Small Cacti texture
    Texture twoSmallCactiTexture;
    if (!twoSmallCactiTexture.loadFromFile("CactiFolder/twoSmallCacti.png")) {
        cerr << "Error: The two SMALL cacti file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Importing Three Small Cacti texture
    Texture threeSmallCactiTexture;
    if (!threeSmallCactiTexture.loadFromFile("CactiFolder/threeSmallCacti.png")) {
        cerr << "Error: The three cacti file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Importing Four Cacti texture
    Texture fourCactiTexture;
    if (!fourCactiTexture.loadFromFile("CactiFolder/fourCacti.png")) {
        cerr << "Error: The four cacti file wasn't found idk wha happend." << endl;
        return -1;
    }

    // Here's the list off all the cacti textures
    vector<Texture> cactiTextures = {singleCactusTexture, singleSmallCactusTexture, twoCactiTexture, twoSmallCactiTexture, threeSmallCactiTexture, fourCactiTexture};


    // Creating the two cacti Sprites
    Sprite cactusSprite1;
    Sprite cactusSprite2;
    cactusSprite1.setTexture(cactiTextures[idx], true);

    switch (currentCactus) {
        case 0: // one cacti
            cactusSprite1.setPosition(3100, 470);
            cactusSprite1.setScale(1.5f, 1.5f);
            break;
        case 1: // one small cacti
            cactusSprite1.setPosition(3100, 500);
            cactusSprite1.setScale(1.2f, 1.2f);
            break;
        case 2: // two cacti
            cactusSprite1.setPosition(3100, 460);
            cactusSprite1.setScale(1.3f, 1.3f);
            break;
        case 3: // two small cacti
            cactusSprite1.setPosition(3100, 501);
            cactusSprite1.setScale(1.2f, 1.2f);
            break;
        case 4: // three small cacti
            cactusSprite1.setPosition(3100, 502);
            cactusSprite1.setScale(1.15f, 1.15f);
            break;
        case 5: // four cacti
            cactusSprite1.setPosition(3100, 463);
            cactusSprite1.setScale(1.25f, 1.25f);
            break;
    }

    idx = cactiRandomizer(mt);
    currentCactus = idx;
    cactusSprite2.setTexture(cactiTextures[idx], true);
    
    switch (currentCactus) {
        case 0: // one cacti
            cactusSprite2.setPosition(3700, 470);
            cactusSprite2.setScale(1.5f, 1.5f);
            break;
        case 1: // one small cacti
            cactusSprite2.setPosition(3700, 500);
            cactusSprite2.setScale(1.2f, 1.2f);
            break;
        case 2: // two cacti
            cactusSprite2.setPosition(3700, 460);
            cactusSprite2.setScale(1.3f, 1.3f);
            break;
        case 3: // two small cacti
            cactusSprite2.setPosition(3700, 501);
            cactusSprite2.setScale(1.2f, 1.2f);
            break;
        case 4: // three small cacti
            cactusSprite2.setPosition(3700, 502);
            cactusSprite2.setScale(1.15f, 1.15f);
            break;
        case 5: // four cacti
            cactusSprite2.setPosition(3700, 463);
            cactusSprite2.setScale(1.25f, 1.25f);
            break;
    }

    pt.setPosition(9000, pt.getPosition().y);


    // CACTUS SPRITES MAKING ENDS HERE: ---------------------------------------------------------------------------------------



    // GROUND SPRITES ARE GONNA BE HERE: --------------------------------------------------------------------------------------

    Texture fullGroundTexture;
    if (!fullGroundTexture.loadFromFile("GroundFolder/fullGround.png")) {
        cerr << "Error: The full ground file wasn't found idk wha happend." << endl;
        return -1;
    }

    Texture flatGroundTexture;
    if (!flatGroundTexture.loadFromFile("GroundFolder/flatPartOfGround.png")) {
        cerr << "Error: The flat ground file wasn't found idk wha happend." << endl;
        return -1;
    }

    Texture singleBumpTexture;
    if (!singleBumpTexture.loadFromFile("GroundFolder/singleBump.png")) {
        cerr << "Error: The single bump file wasn't found idk wha happend." << endl;
        return -1;
    }

    Texture bumpyGroundTexture;
    if (!bumpyGroundTexture.loadFromFile("GroundFolder/bumpyPartsOfGround.png")) {
        cerr << "Error: The bumpy ground file wasn't found idk wha happend." << endl;
        return -1;
    }

    Texture bumpAndDivotTexture;
    if (!bumpAndDivotTexture.loadFromFile("GroundFolder/bumpAndDivot.png")) {
        cerr << "Error: The bump and divot file wasn't found idk wha happend." << endl;
        return -1;
    }
    

    vector<Texture> groundTextures = {fullGroundTexture, flatGroundTexture, bumpyGroundTexture, singleBumpTexture, bumpAndDivotTexture};
    vector<Sprite> theGround;
    float x = 0;

    // Making the intial ground for the start of the game
    while (x < 2000) {
        idx = groundRandomizer(mt);
        Sprite groundSeg;
        groundSeg.setTexture(groundTextures[idx], true);
        groundSeg.setScale(1.2f, 1.2f);
        groundSeg.setPosition(x - 5, 550);

        auto segBound = groundSeg.getGlobalBounds(); 

        x += segBound.width;
        theGround.push_back(move(groundSeg));
    }
    
    // GROUND SPRITES END HERE: -----------------------------------------------------------------------------------------------

    // HIT BOXES OF SPRITES: --------------------------------------------------------------------------------------------------


    // ------------------------------------------------------------------------------------------------------------------------

    // WINDOW FOR GAME SCREEN STARTS HERE: ------------------------------------------------------------------------------------
    
    while (dinoScreen.isOpen()) {
        // Time since last frames
        float deltaTime = clock.restart().asSeconds();
        static float timeSinceLastFrame = 0.0f;
        static float timeSinceLastFrame2 = 0.0f;
        static float timeSinceLastFrame3 = 0.0f;
        static float timeSinceLastFrame4 = 0.0f;
        static float timeSinceLastFrame5 = 0.0f;


        static float gameTime = 0.0f;
        gameTime += deltaTime;
        distanceCalculation = (distance)/(gameTime * -(speed/6));
        
        
        timeSinceLastFrame += deltaTime;
        timeSinceLastFrame2 += deltaTime;
        timeSinceLastFrame3 += deltaTime;
        timeSinceLastFrame4 += deltaTime;        
        timeSinceLastFrame5 += deltaTime;        
        
        if (!isDead) {
            if (speed > -1300) {
                speed -= 0.002;
            } 
        }        
        

        // distance score:
        if (!isDead) {
            if (timeSinceLastFrame3 > distanceCalculation) {
                
                distance++;
                scoreText.setString(to_string(distance));
                timeSinceLastFrame3 = 0.0f;

                if (distance == 1) {
                    zeroString = "0000";
                    zeros.setString(zeroString);
                    scoreText.setPosition(scoreText.getPosition().x, 10);                
                }
                if (distance == 10) {
                    zeroString = "000";
                    zeros.setString(zeroString);
                    scoreText.setPosition(scoreText.getPosition().x - 35, 10);                
                }
                if (distance == 100) {
                    zeroString = "00";
                    zeros.setString(zeroString);
                    scoreText.setPosition(scoreText.getPosition().x - 35, 10);                
                } 

                if (distance == 1000) {
                    zeroString = "0";
                    zeros.setString(zeroString);
                    scoreText.setPosition(scoreText.getPosition().x - 35, 10);                
                }    

                if (distance == 10000) {
                    zeroString = "";
                    zeros.setString(zeroString);
                    scoreText.setPosition(scoreText.getPosition().x - 35, 10);                
                } 


            }

        }


        // blinking every 100 meters:
        if (distance % 100 == 0 && distance != 0) {
            every100Meters = true;
                if (!is100MeterSFXPlayed) {
                    meters_100.play();
                    is100MeterSFXPlayed = true;
                }            
        }

        if (every100Meters) {
            if (distance % 100 != 24) {
                every100MetersMarked = distance;
                scoreText.setString(to_string(every100MetersMarked));
                if (!isDead) {
                    if (timeSinceLastFrame5 >= blinkingDuration) {
                        if (isScoreGone) {
                            zeros.setPosition(zeros.getPosition().x, 10);
                            scoreText.setPosition(scoreText.getPosition().x, 10);
                            // cout << "Score is coming back on screen" << endl;
                        }
                        else {
                            zeros.setPosition(zeros.getPosition().x, -70);
                            scoreText.setPosition(scoreText.getPosition().x, -70);
                            // cout << "Score is going off screen" << endl;
                        }
                        isScoreGone = !isScoreGone;
                        timeSinceLastFrame5 = 0.0f;
                    }
                }
                else {
                    zeros.setPosition(zeros.getPosition().x, 10);
                    scoreText.setPosition(scoreText.getPosition().x, 10);
                }
            }
            else {
                every100Meters = false;
                zeros.setPosition(zeros.getPosition().x, 10);
                scoreText.setString(to_string(distance));
                scoreText.setPosition(scoreText.getPosition().x, 10);
                is100MeterSFXPlayed = false;

            }
        }

        // SETTING ALL THE RANDOMIZERS EVERY SECOND
        idx = cactiRandomizer(mt);
        currentCactus = idx;
        cactus1distance = dist(mt);
        cactus2distance = dist2(mt);
        cloudYLevel = cloudYLevelRandomizer(mt);
        cloudSpeed = cloudSpeedRandomizer(mt);
        cloudSize = cloudSizeRandomizer(mt);
        ptDistance = ptDistanceRandomizer(mt);
        ptYLevel = ptYLevelRandomizer(mt);

        auto cactusBounds = cactusSprite1.getGlobalBounds();
        cactusBounds.width -= 12.0f;
        cactusBounds.height -= 20.0f;
        cactusBounds.left += 6.0f;
        auto cactusBounds2 = cactusSprite2.getGlobalBounds();
        cactusBounds2.width -= 12.0f;
        cactusBounds2.height -= 18.0f;
        cactusBounds.left += 6.0f;
        dinoBounds = dinoFrameSprite.getGlobalBounds();
        float yOffset = groundCoord - dinoBounds.height; // height of the dinosaur on top of the ground
        ptBounds = pt.getGlobalBounds();

        // float dinoContactX = dinoBounds.top + dinoBounds.height - 10;
        FloatRect shrunk = dinoBounds;
        shrunk.left += 20;
        shrunk.width -= 35.f;
        shrunk.height -= 24.f;
        shrunk.top += 22.f;


        dinoHitBoxLeft.setPosition(shrunk.left + 15, 0);
        dinoHitBoxRight.setPosition(shrunk.left, 0);


        FloatRect ptShrunk = ptBounds;
        // PTERODACTYL HITBOX
        ptHitBoxLeft.setPosition(ptShrunk.left, 0);
        ptHitBoxRight.setPosition(ptShrunk.left + ptShrunk.width, 0);
        ptTop.setPosition(0, ptShrunk.top);
        ptBottom.setPosition(0, ptShrunk.top + ptShrunk.height);     
        
        ptHitBoxLeft.setSize(Vector2f(2, 900));
        ptHitBoxRight.setSize(Vector2f(2, 900));
        ptTop.setSize(Vector2f(1600, 2));
        ptBottom.setSize(Vector2f(1600, 2));

        ptShrunk.top -= 20.0f;
        ptShrunk.height -= 10.0f;
        ptShrunk.width -= 10.0f;

        // PTERODACTYL HITBOX
        pterodactylHead.setPosition(ptShrunk.left + 5, ptShrunk.top + 40);
        pterodactylBody1.setPosition(ptShrunk.left + 35, ptShrunk.top + 60);
        pterodactylBody2.setPosition(ptShrunk.left + 41, ptShrunk.top + 62);
        // pterodactylUpperWing1.setPosition(ptShrunk.left + 38.252, ptShrunk.top + 23);
        pterodactylUpperWing2.setPosition(ptShrunk.left + 37.252, ptShrunk.top + 25);
        pterodactylUpperWing3.setPosition(ptShrunk.left + 55.252, ptShrunk.top + 40);
        


        // Event object captures user input
        Event event;

        while (dinoScreen.pollEvent(event)) {
            if (event.type == Event::Closed) { // I'm assuming this means that it checks if the user presses x on the window
                dinoScreen.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) { // if the user presses space
                if (isDead) {
                    dist2 = std::uniform_int_distribution<int>(2400, 2450);
                    cactus2distance = dist2(mt);
                    switch (currentCactus) {
                        case 0: // one cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 470);
                            cactusSprite1.setScale(1.5f, 1.5f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 470);
                            cactusSprite2.setScale(1.5f, 1.5f);
                            break;
                        case 1: // one small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 500);
                            cactusSprite1.setScale(1.2f, 1.2f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 500);
                            cactusSprite2.setScale(1.2f, 1.2f);
                            break;
                        case 2: // two cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 460);
                            cactusSprite1.setScale(1.3f, 1.3f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 460);
                            cactusSprite2.setScale(1.3f, 1.3f);
                            break;
                        case 3: // two small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 501);
                            cactusSprite1.setScale(1.2f, 1.2f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 501);
                            cactusSprite2.setScale(1.2f, 1.2f);
                            break;
                        case 4: // three small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 502);
                            cactusSprite1.setScale(1.15f, 1.15f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 502);
                            cactusSprite2.setScale(1.15f, 1.15f);
                            break;
                        case 5: // four cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 463);
                            cactusSprite1.setScale(1.25f, 1.25f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 463);
                            cactusSprite2.setScale(1.25f, 1.25f);
                            break;
                    }

                    switch (ptYLevel) {                     // RANDOMIZING THE PTERODACTYL POSITION
                        case 1:
                            pt.setPosition(ptDistance, 470);
                            // cout << "Resetting game: pterodactyl distance 1" << endl;
                            break;
                        case 2:
                            pt.setPosition(ptDistance, 405);
                            // cout << "Resetting game: pterodactyl distance 2" << endl;
                            break;
                        case 3:
                            pt.setPosition(ptDistance, 350);
                            // cout << "Resetting game: pterodactyl distance 3" << endl;
                            break;
                    }
    
                    isDead = false;
                    every100Meters = false;
                    gameOver.setPosition(800, -200);
                    resetButton.setPosition(800, -200);
                    zeros.setPosition(zeros.getPosition().x, 10);
                    scoreText.setPosition(scoreText.getPosition().x, 10);

                    cloudSize = cloudSizeRandomizer(mt);                // CHANGING UP THE CLOUDS
                    cloud.setPosition(cactus1distance, cloudYLevel);
                    cloud.setScale(cloudSize, cloudSize);

                    cloudSize = cloudSizeRandomizer(mt);
                    cactus1distance = dist(mt);
                    cloudYLevel = cloudYLevelRandomizer(mt);
                    cloud2.setPosition(cactus1distance, cloudYLevel);
                    cloud.setScale(cloudSize, cloudSize);
                    scoreText.setPosition(1560.f, 10.f);     
                    zeros.setPosition(1560 - (4 * 35), 10.f);      
                    zeroString = "0000";
                    zeros.setString(zeroString);

                    if (maxDistance < distance) { // FOR CHANGING THE HIGHSCORE IF THE USER GOES FURTHER THAN HIGHSCORE DISTANCE
                        maxDistance = distance;
                        HighScore.setString(to_string(maxDistance));
                        if (maxDistance > 10000) {
                            // cout << "maxDistance is greater than 10000, and user pressed space." << endl;
                            zeroString2 = "";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1175 + 35, 10);
                        }
                        else if (maxDistance > 1000) {
                            // cout << "maxDistance is greater than 1000, and user pressed space." << endl;
                            zeroString2 = "0";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1210 + 35, 10);
                        }
                        else if (maxDistance > 100) {
                            // cout << "maxDistance is greater than 100, and user pressed space." << endl;
                            zeroString2 = "00";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1245 + 35, 10);
                        }
                        else if (maxDistance > 10) {
                            // cout << "maxDistance is greater than 10, and user pressed space." << endl;
                            zeroString2 = "000";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1280 + 35, 10);
                        }                        
                    } 

                    // cout << HighScore.getPosition().x - (1 * 35) << endl;
                    // cout << HighScore.getPosition().x - (2 * 35) << endl;
                    // cout << HighScore.getPosition().x - (3 * 35) << endl;
                    // cout << HighScore.getPosition().x - (4 * 35) << endl;

                    distance = 0;
                    speed = -600;
                    ptFrameDuration = 0.5f;
                    gameTime = 0;
                    distanceCalculation = 0.1f;
                    every100Meters = false;

                }

                dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition - (3 * 88), dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
                if (!isJumping) { // if the dino is already jumping
                    Y_Velocity = jumpVelocity; // the dino's y velocity will be negative, making the dino fall
                    isJumping = true;   
                    jump.play();               
                    
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) { // if the user presses space
                dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition - (3 * 88), dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
                if (!isJumping) { // if the dino is already jumping
                    Y_Velocity = jumpVelocity; // the dino's y velocity will be negative, making the dino fall
                    isJumping = true;                    
                    jump.play();
                }
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
                if (!isJumping && !isDead) {
                    Y_Velocity = 0.0f; // stops vertical movement
                    isDucking = true;
                }

                if (isJumping) {
                    Y_Velocity += gravity * 1450 * deltaTime; // increases the negative velocity due to gravity
                    // cout << "User is pressing the down key while jumping" << endl;
                }
            }

            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down) {
                isDucking = false;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // 1) Get the click in world coords
                sf::Vector2i pixelPos{event.mouseButton.x, event.mouseButton.y};
                sf::Vector2f worldPos = dinoScreen.mapPixelToCoords(pixelPos);
                // cout << "X: " << event.mouseButton.x << " Y: " << event.mouseButton.y<< endl;

                // 2) See if it hit the sprite
                if (resetButton.getGlobalBounds().contains(worldPos)) {
                    // 3) It did—do your action!
                    // e.g. toggle a flag, play a sound, change texture...
                    dist2 = std::uniform_int_distribution<int>(2400, 2450);
                    cactus2distance = dist2(mt);
                    switch (currentCactus) {
                        case 0: // one cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 470);
                            cactusSprite1.setScale(1.5f, 1.5f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 470);
                            cactusSprite2.setScale(1.5f, 1.5f);
                            break;
                        case 1: // one small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 500);
                            cactusSprite1.setScale(1.2f, 1.2f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 500);
                            cactusSprite2.setScale(1.2f, 1.2f);
                            break;
                        case 2: // two cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 460);
                            cactusSprite1.setScale(1.3f, 1.3f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 460);
                            cactusSprite2.setScale(1.3f, 1.3f);
                            break;
                        case 3: // two small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 501);
                            cactusSprite1.setScale(1.2f, 1.2f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 501);
                            cactusSprite2.setScale(1.2f, 1.2f);
                            break;
                        case 4: // three small cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 502);
                            cactusSprite1.setScale(1.15f, 1.15f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 502);
                            cactusSprite2.setScale(1.15f, 1.15f);
                            break;
                        case 5: // four cacti
                            cactusSprite1.setTexture(cactiTextures[idx], true);
                            cactusSprite1.setPosition(cactus1distance, 463);
                            cactusSprite1.setScale(1.25f, 1.25f);

                            cactusSprite2.setTexture(cactiTextures[idx], true);
                            cactusSprite2.setPosition(cactus2distance, 463);
                            cactusSprite2.setScale(1.25f, 1.25f);
                            break;
                    }

                    switch (ptYLevel) { // RANDOM PTERODACTYL Y LEVEL
                        case 1:
                            pt.setPosition(ptDistance, 470);
                            break;
                        case 2:
                            pt.setPosition(ptDistance, 405);
                            break;
                        case 3:
                            pt.setPosition(ptDistance, 350);
                            break;
                    }
                    
                    isDead = false;
                    every100Meters = false;
                    gameOver.setPosition(800, -200);
                    resetButton.setPosition(800, -200);
                    zeros.setPosition(zeros.getPosition().x, 10);
                    scoreText.setPosition(scoreText.getPosition().x, 10);
                    cloud.setPosition(cactus1distance, cloudYLevel);
                    cactus1distance = dist(mt);
                    cloudYLevel = cloudYLevelRandomizer(mt);
                    cloud2.setPosition(cactus1distance, cloudYLevel);
                    scoreText.setPosition(1560.f, 10.f);      
                    zeros.setPosition(1560 - (4 * 35), 10.f);      
                    zeroString = "0000";
                    zeros.setString(zeroString);

                    if (maxDistance < distance) {
                        maxDistance = distance;
                        HighScore.setString(to_string(maxDistance));
                        if (maxDistance > 10000) {
                            // cout << "maxDistance is greater than 10000, and user clicked on the reset button." << endl;
                            zeroString2 = "";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1175 + 35, 10);
                        }
                        else if (maxDistance > 1000) {
                            // cout << "maxDistance is greater than 1000, and user clicked on the reset button." << endl;
                            zeroString2 = "0";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1210 + 35, 10);
                        }
                        else if (maxDistance > 100) {
                            // cout << "maxDistance is greater than 100, and user clicked on the reset button." << endl;
                            zeroString2 = "00";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1245 + 35, 10);
                        }
                        else if (maxDistance > 10) {
                            // cout << "maxDistance is greater than 10, and user clicked on the reset button." << endl;
                            zeroString2 = "000";
                            zeross.setString(zeroString2);
                            HighScore.setPosition(1280 + 35, 10);
                        }                        
                    } 

                    distance = 0;
                    speed = -600;
                    ptFrameDuration = 0.5f;
                    gameTime = 0;
                    distanceCalculation = 0.1f;
                    every100Meters = false;   
                }
            }
        }

        // Moving the cacti and ground to the left ----------------------------------------------------------------
        if (!dinoHead.getGlobalBounds().intersects(cactusBounds) && // IF THE DINO INTERSECTS THE FIRST CACTUS
            !dinoBody1.getGlobalBounds().intersects(cactusBounds) && 
            !dinoBody2.getGlobalBounds().intersects(cactusBounds) && 
            !dinoBody3.getGlobalBounds().intersects(cactusBounds) && 
            !dinoBody4.getGlobalBounds().intersects(cactusBounds) && 
            
            !dinoHead.getGlobalBounds().intersects(cactusBounds2) && // IF THE DINO INTERSECTS THE SECOND CACTUS
            !dinoBody1.getGlobalBounds().intersects(cactusBounds2) && 
            !dinoBody2.getGlobalBounds().intersects(cactusBounds2) && 
            !dinoBody3.getGlobalBounds().intersects(cactusBounds2) && 
            !dinoBody4.getGlobalBounds().intersects(cactusBounds2) && 

            !dinoHead.getGlobalBounds().intersects(pterodactylHead.getGlobalBounds()) && // IF THE DINO INTERSECTS THE PTERODACTYL
            !dinoBody1.getGlobalBounds().intersects(pterodactylHead.getGlobalBounds()) && 
            !dinoBody2.getGlobalBounds().intersects(pterodactylHead.getGlobalBounds()) && 
            !dinoBody3.getGlobalBounds().intersects(pterodactylHead.getGlobalBounds()) && 
            !dinoBody4.getGlobalBounds().intersects(pterodactylHead.getGlobalBounds()) &&
            
            !dinoHead.getGlobalBounds().intersects(pterodactylBody1.getGlobalBounds()) && // IF THE DINO INTERSECTS THE PTERODACTYL
            !dinoBody1.getGlobalBounds().intersects(pterodactylBody1.getGlobalBounds()) && 
            !dinoBody2.getGlobalBounds().intersects(pterodactylBody1.getGlobalBounds()) && 
            !dinoBody3.getGlobalBounds().intersects(pterodactylBody1.getGlobalBounds()) && 
            !dinoBody4.getGlobalBounds().intersects(pterodactylBody1.getGlobalBounds()))  { 


            isDead = false;
            isDeadSFXPlayed = false;
            gameOver.setPosition(800, -200);
            resetButton.setPosition(800, -200);
            cactusSprite1.move(speed * deltaTime, 0); // dino will keep moving
            cactusSprite2.move(speed * deltaTime, 0);

            // pterodactyl hitbox movement
            ptHitBoxLeft.move(speed * deltaTime, 0);
            ptHitBoxRight.move(speed * deltaTime, 0);
            ptTop.move(speed * deltaTime, 0);
            ptBottom.move(speed * deltaTime, 0);
            
            pt.move(speed * deltaTime, 0);
            cloud.move((cloudSpeed) * deltaTime, 0);
            cloudSpeed = cloudSpeedRandomizer(mt);
            cloud2.move((cloudSpeed) * deltaTime, 0);

            for (auto &seg : theGround) {
                seg.move(speed * deltaTime, 0);
            }

        }
        else {
            isDead = true;
        }
        // --------------------------------------------------------------------------------------------------------

        // Adding more ground to the right ------------------------------------------------------------------------
        if (theGround.front().getGlobalBounds().left + theGround.front().getGlobalBounds().width < 0) {
            theGround.erase(theGround.begin());
        }    

        if (theGround.back().getGlobalBounds().left + theGround.back().getGlobalBounds().width < 1700) {
            Sprite newGround;

            idx = groundRandomizer(mt);
            newGround.setTexture(groundTextures[idx], true);
            newGround.setScale(1.2f, 1.2f);

            float newX = theGround.back().getGlobalBounds().left + theGround.back().getGlobalBounds().width;
            newGround.setPosition(newX - 5, 550);

            theGround.push_back(move(newGround));
        }

        // --------------------------------------------------------------------------------------------------------


        // Dino Sprite Animation 

        if (isDead) {
            dinoFrameSprite.setTexture(dinoFrameTexture);
            dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition + 88, dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
            dinoFrameSprite.setPosition(40, dinoFrameSprite.getPosition().y);
            gameOver.setPosition(500, 250);
            resetButton.setPosition(730, 300);
                if (!isDeadSFXPlayed) {
                    death.play();
                    isDeadSFXPlayed = true;
                }            
        }
        else if (isJumping) {
            // Apply gravity and update position of dino
            Y_Velocity += gravity * 2.1 * deltaTime; // increases the negative velocity due to gravity
            dinoFrameSprite.move(0, Y_Velocity * deltaTime); // update sprite's position
            dinoHead.move(0, Y_Velocity * deltaTime);
            dinoBody1.move(0, Y_Velocity * deltaTime);
            dinoBody2.move(0, Y_Velocity * deltaTime);
            dinoBody3.move(0, Y_Velocity * deltaTime);
            dinoBody4.move(0, Y_Velocity * deltaTime);
            
            
            dinoFrameSprite.setTexture(dinoFrameTexture);
            dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition - (3 * 88), dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
        }
        else if (isDucking) {
            dinoFrameSprite.setTexture(dinoDuckingFrame1 ? dinoDucking1 : dinoDucking2, /*resetRect=*/true);
            duckBounds = dinoFrameSprite.getGlobalBounds();
            duckH = duckBounds.height;
            yOffset = groundCoord - duckH;
            dinoFrameSprite.setPosition(40.f, yOffset);
            if (timeSinceLastFrame >= dinoFrameDuration) {
                dinoDuckingFrame1 = !dinoDuckingFrame1;
                timeSinceLastFrame = 0.0f; // Resets the timer
            }
        }
        else { // if dino isn't jumping, ducking, or dead
            if (timeSinceLastFrame >= dinoFrameDuration) {
                dinoFrameSprite.setTexture(dinoFrameTexture, true);
                dinoFrameSprite.setPosition(40, groundCoord - dinoBounds.height);

                if (dinoRunningFrame1) {
                    dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition - 88, dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
                }
                else {
                    dinoFrameSprite.setTextureRect(IntRect(dinoFrameXPosition, dinoFrameYPosition, dinoFrameWidth, dinoFrameHeight));
                }
                dinoRunningFrame1 = !dinoRunningFrame1;
                timeSinceLastFrame = 0.0f; // Resets the timer

                //DINO HITBOX
                dinoHead.setPosition(91, 478);
                dinoBody1.setPosition(42, 513);
                dinoBody2.setPosition(50, 546);
                dinoBody3.setPosition(51, 546);
                dinoBody4.setPosition(64, 561);
                
            }
        }

        // Pterodactyl Animation
        if (timeSinceLastFrame2 >= ptFrameDuration) {
            if (!isDead) {
                pt.setTexture(ptFlapDown, true);
                if (ptFlap1) {
                    pt.setTexture(ptFlapUp, true);
                }
                else {
                    pt.setTexture(ptFlapDown, true);
                }
                ptFlap1 = !ptFlap1;
                timeSinceLastFrame2 = 0.0f; // Resets the timer
            }
        }

        ptFrameDuration -= -speed/60000000000;

        if (ptFlap1) {
            if (dinoHead.getGlobalBounds().intersects(pterodactylUpperWing2.getGlobalBounds()) && // IF THE DINO INTERSECTS THE PTERODACTYL
            dinoBody1.getGlobalBounds().intersects(pterodactylUpperWing2.getGlobalBounds()) && 
            dinoBody2.getGlobalBounds().intersects(pterodactylUpperWing2.getGlobalBounds()) && 
            dinoBody3.getGlobalBounds().intersects(pterodactylUpperWing2.getGlobalBounds()) && 
            dinoBody4.getGlobalBounds().intersects(pterodactylUpperWing2.getGlobalBounds()) &&
        
            dinoHead.getGlobalBounds().intersects(pterodactylUpperWing3.getGlobalBounds()) && // IF THE DINO INTERSECTS THE PTERODACTYL
            dinoBody1.getGlobalBounds().intersects(pterodactylUpperWing3.getGlobalBounds()) && 
            dinoBody2.getGlobalBounds().intersects(pterodactylUpperWing3.getGlobalBounds()) && 
            dinoBody3.getGlobalBounds().intersects(pterodactylUpperWing3.getGlobalBounds()) && 
            dinoBody4.getGlobalBounds().intersects(pterodactylUpperWing3.getGlobalBounds())) {

                isDead = true;
            }
            else {
                if (dinoHead.getGlobalBounds().intersects(pterodactylBody2.getGlobalBounds()) && // IF THE DINO INTERSECTS THE PTERODACTYL
                    dinoBody1.getGlobalBounds().intersects(pterodactylBody2.getGlobalBounds()) && 
                    dinoBody2.getGlobalBounds().intersects(pterodactylBody2.getGlobalBounds()) && 
                    dinoBody3.getGlobalBounds().intersects(pterodactylBody2.getGlobalBounds()) && 
                    dinoBody4.getGlobalBounds().intersects(pterodactylBody2.getGlobalBounds())) {

                        isDead = true;
                }

            }
        }

        // Checks if sprite has landed
        if (dinoFrameSprite.getPosition().y + duckH >= groundCoord) {
            dinoFrameSprite.setPosition(dinoFrameSprite.getPosition().x, groundCoord - duckH); // Reset to ground level
            Y_Velocity = 0.0f; // stops vertical movement
            isJumping = false; // allows the dino to jump again
        }
        
        if (dinoFrameSprite.getPosition().y + dinoBounds.height >= groundCoord) {
            dinoFrameSprite.setPosition(dinoFrameSprite.getPosition().x, groundCoord - dinoBounds.height); // Reset to ground level
            Y_Velocity = 0.0f; // stops vertical movement
            isJumping = false; // allows the dino to jump again
        }

        auto cloudBounds = cloud.getGlobalBounds();
        auto cloudBounds2 = cloud2.getGlobalBounds();
        
        if (cloudBounds.left + cloudBounds.width < 0) { 
            cloud.setPosition(cactus1distance, cloudYLevel);
        }
        if (cloudBounds2.left + cloudBounds2.width < 0) { 
            cloudYLevel = cloudYLevelRandomizer(mt);
            cloud2.setPosition(cactus1distance + 300, cloudYLevel);
        }



        spacing = spacingRandomizer(mt);
        // SPACING BETWEEN THE CACTI AND PTERODACTYL: ------------------------------------------------------------------

        if (ptBounds.left > cactusBounds.left) { // if the pterodactyl is behind cactus1
            if (ptBounds.left - (cactusBounds.left + cactusBounds.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150; 
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                      
                pt.setPosition(pt.getPosition().x + spacing + 100, pt.getPosition().y);
            }     
        }

        if (ptBounds.left > cactusBounds2.left) { // if the pterodactyl is behind cactus1
            if (ptBounds.left - (cactusBounds2.left + cactusBounds2.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150;
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                pt.setPosition(pt.getPosition().x + spacing + 200, pt.getPosition().y);
            }     
        }


        if (cactusBounds.left > cactusBounds2.left) { // if cactus1 is behind cactus2
            if (cactusBounds.left - (cactusBounds2.left + cactusBounds2.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150;  
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                cactusSprite1.setPosition(cactusSprite1.getPosition().x + spacing + 100, cactusSprite1.getPosition().y);            
            }     
        }

        if (cactusBounds.left > ptBounds.left) { // if cactus1 is behind the pterodactyl
            if (cactusBounds.left - (ptBounds.left + ptBounds.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150;    
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                cactusSprite1.setPosition(cactusSprite1.getPosition().x + spacing + 250, cactusSprite1.getPosition().y);            
            }     
        }


        if (cactusBounds2.left > cactusBounds.left) { // if cactus2 is behind cactus1
            if (cactusBounds2.left - (cactusBounds.left + cactusBounds.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150;  
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                cactusSprite2.setPosition(cactusSprite2.getPosition().x + spacing + 100, cactusSprite2.getPosition().y);
            }     
        }

        if (cactusBounds2.left > ptBounds.left) { // if cactus2 is behind the pterodactyl
            if (cactusBounds2.left - (ptBounds.left + ptBounds.width) < 550) {
                if (speed < -850) spacing += 50;
                if (speed < -950) spacing += 100;
                if (speed < -1050) spacing += 150;  
                if (speed < -1100) spacing += 200;  
                if (speed < -1250) spacing += 250;  
                cactusSprite2.setPosition(cactusSprite2.getPosition().x + spacing + 200, cactusSprite2.getPosition().y);
            }     
        }
        // ---------------------------------------------------------------------------------------------------------------


        // Pterodactyl teleports back to right side
        if (ptBounds.left + ptBounds.width < 0) {
            switch (ptYLevel) {
                case 1:
                    pt.setPosition(ptDistance, 470);
                    // cout << "pt distance 1" << endl;
                    break;
                case 2:
                    pt.setPosition(ptDistance, 405);
                    // cout << "pt distance 2" << endl;
                    break;
                case 3:
                    pt.setPosition(ptDistance, 350);
                    // cout << "pt distance 3" << endl;
                    break;
            }
        }
        
        if (cactusBounds.left + cactusBounds.width < 0) {     // first cacti sprite
            cactus1distance = dist(mt);
            switch (currentCactus) {
                case 0: // one cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 470);
                    cactusSprite1.setScale(1.5f, 1.5f);
                    break;
                case 1: // one small cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 500);
                    cactusSprite1.setScale(1.2f, 1.2f);
                    break;
                case 2: // two cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 460);
                    cactusSprite1.setScale(1.3f, 1.3f);
                    break;
                case 3: // two small cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 501);
                    cactusSprite1.setScale(1.2f, 1.2f);
                    break;
                case 4: // three small cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 502);
                    cactusSprite1.setScale(1.15f, 1.15f);
                    break;
                case 5: // four cacti
                    cactusSprite1.setTexture(cactiTextures[idx], true);
                    cactusSprite1.setPosition(cactus1distance, 463);
                    cactusSprite1.setScale(1.25f, 1.25f);
                    break;
            }
        }
        
        if (cactusBounds2.left + cactusBounds2.width < 0) {      // second cacti sprite
            dist2 = std::uniform_int_distribution<int>(1670, 1790);
            cactus2distance = dist2(mt);
            switch (currentCactus) {
                case 0: // one cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 470);
                    cactusSprite2.setScale(1.5f, 1.5f);
                    break;
                case 1: // one small cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 500);
                    cactusSprite2.setScale(1.2f, 1.2f);
                    break;
                case 2: // two cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 460);
                    cactusSprite2.setScale(1.3f, 1.3f);
                    break;
                case 3: // two small cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 501);
                    cactusSprite2.setScale(1.2f, 1.2f);
                    break;
                case 4: // three small cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 502);
                    cactusSprite2.setScale(1.15f, 1.15f);
                    break;
                case 5: // four cacti
                    cactusSprite2.setTexture(cactiTextures[idx], true);
                    cactusSprite2.setPosition(cactus2distance, 463);
                    cactusSprite2.setScale(1.25f, 1.25f);
                    break;
            }
        }


        // Sets background color
        if (dayOrNight == 1) {
            dinoScreen.clear(Color::White);
        }
        else {
            dinoScreen.clear(gray);
        }

        dinoScreen.draw(scoreText);
        dinoScreen.draw(zeros);
        dinoScreen.draw(zeross);
        dinoScreen.draw(High);
        dinoScreen.draw(HighScore);

        // DINO HITBOX LINES
        // dinoScreen.draw(dinoHitBoxLeft); 
        // dinoScreen.draw(dinoHitBoxRight);      
        
        // CACTUS HITBOX LINES
        // dinoScreen.draw(ptHitBoxLeft);
        // dinoScreen.draw(ptHitBoxRight);
        // dinoScreen.draw(ptTop);
        // dinoScreen.draw(ptBottom);

        for (auto &seg : theGround) {
            // cout<<"ground here"<<endl;
            dinoScreen.draw(seg);
        }

        dinoScreen.draw(cloud);
        dinoScreen.draw(cloud2);
        dinoScreen.draw(dinoFrameSprite);
        dinoScreen.draw(cactusSprite1);
        dinoScreen.draw(cactusSprite2);
        dinoScreen.draw(pt);
        dinoScreen.draw(gameOver);
        dinoScreen.draw(resetButton);
        
        // dinoScreen.draw(pterodactylHead); 
        // dinoScreen.draw(pterodactylBody1); 
        // dinoScreen.draw(pterodactylBody2); 
        // dinoScreen.draw(pterodactylUpperWing1);
        // dinoScreen.draw(pterodactylUpperWing2);
        // dinoScreen.draw(pterodactylUpperWing3);
        
        // dinoScreen.draw(dinoBody3);         
        // dinoScreen.draw(dinoBody4); 


        // Displays the window
        dinoScreen.display();
    }

    // cout << "this is the Distance: " << distance << endl;
    // cout << "this is the maxDistance: " << maxDistance << endl;

    return 0;
}