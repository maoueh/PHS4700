#include "application_manager.h"
#include "command_line.h"
#include "tp1_constants.h"
#include "tp1_simulation_1.h"
#include "tp1_simulation_2.h"

void promptInitialPosition(Vector& initialPosition);
void promptInitialVelocity(Vector& initialVelocity);

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    
    do
    {
        STRING simulationType;
        cout << "Entrez le type de simulation (1 ou 2 ou q pour quitter) : ";
        getline(cin, simulationType);

        UINT quitLetterPosition = simulationType.find("q");
        if ( quitLetterPosition != string::npos )
            return 0;

        UINT automaticLetterPosition = simulationType.find("a");

        BOOL promptPosition = automaticLetterPosition == string::npos;
        BOOL promptVelocity = automaticLetterPosition == string::npos;

        Vector initialPosition = Tp1Constants::INITIAL_POSITION;
        Vector initialVelocity = Tp1Constants::INITIAL_VELOCITY;

        if ( promptPosition )
            promptInitialPosition(initialPosition);
        if ( promptVelocity )
            promptInitialVelocity(initialVelocity);

        cout << endl << "Fermer la fenetre pour recommencer une simulation ou terminer le programme" << endl << endl;

        UINT type1Position = simulationType.find("1");
        if ( type1Position != string::npos ) // Simulation 1 
            ApplicationManager::get()->startApplication(new Tp1Simulation1(&commandLine, 
                                                                           initialPosition, 
                                                                           initialVelocity));
        else                                 // Simulation 2
            ApplicationManager::get()->startApplication(new Tp1Simulation2(&commandLine, 
                                                                           initialPosition, 
                                                                           initialVelocity));

        // Les resultat sont afficher dans la simulation directement

        ApplicationManager::destroy();

    } while( TRUE );

    return 0;
}

void promptInitialPosition(Vector& initialPosition)
{
    BOOL validPosition = FALSE;
    do
    {
        STRING initialPositionString;
        cout << "Entrez la position initiale comme suit X0, Y0, Z0: ";
        getline(cin, initialPositionString);

        CHAR* nextToken = NULL;
        INT tokenCount = 0;
        CHAR* token = strtok_s((CHAR*) initialPositionString.c_str(), ",", &nextToken);
        while (token != NULL && tokenCount < 3) 
        {
            initialPosition[tokenCount] = (FLOAT) atof(token);
            tokenCount++;
	        token = strtok_s(NULL, ",", &nextToken);
        }

        validPosition = TRUE;
        if ( tokenCount != 3 )
        {
            cout << "Nombre de composants invalide" << endl;
            validPosition = FALSE;
        }

        if ( initialPosition.x() < 0.0f || initialPosition.x() > Tp1Constants::PLAYER_ZONE_WIDTH )
        {
            cout << "Valeur en X invalide" << endl;
            validPosition = FALSE;
        }

        if ( initialPosition.y() < 0.0f || initialPosition.y() > Tp1Constants::PLAYER_ZONE_LENGTH )
        {
            cout << "Valeur en Y invalide" << endl;
            validPosition = FALSE;
        }

        if ( initialPosition.z() < 0.0f || initialPosition.z() > Tp1Constants::COURT_REACH )
        {
            cout << "Valeur en Z invalide" << endl;
            validPosition = FALSE;
        }

        if ( !validPosition )
            cout << "Position initiale invalide, veuillez recommencer" << endl << endl;

    } while( !validPosition );
}

void promptInitialVelocity(Vector& initialVelocity)
{
    BOOL validVelocity = FALSE;
    do
    {
        STRING initialVelocityString;
        cout << "Entrez la vitesse initiale comme suit Vx, Vy, Vz: ";
        getline(cin, initialVelocityString);

        CHAR* nextToken = NULL;
        INT tokenCount = 0;
        CHAR* token = strtok_s((CHAR*) initialVelocityString.c_str(), ", ", &nextToken);
        while (token != NULL && tokenCount < 3) {
            initialVelocity[tokenCount++] = (FLOAT) atof(token);
	        token = strtok_s(NULL, ", ", &nextToken);
        }

        validVelocity = tokenCount == 3;
        if ( !validVelocity )
        {
            cout << "Nombre de composants invalide" << endl;
            cout << "Vitesse initiale invalide, veuillez recommencer" << endl << endl;
        }

    } while( !validVelocity );
}

