#include "application_manager.h"
#include "command_line.h"
#include "tp2_constants.h"
#include "tp2_simulation.h"

BOOL promptData(Vector4d& initialLinearVelocity, Vector4d& initialAngularVelocity);
void promptLinearVelocity(Vector4d& initialLinearVelocity);
void promptAngularVelocity(Vector4d& initialAngularVelocity);

BOOL gFirstRun = true;

int main(int argumentCount, const CHAR** arguments)
{
    CommandLine commandLine(argumentCount, arguments);
    
    BOOL continueLoop = !Tp2Constants::SKIP_DATA_INPUT;
    do
    {
        Vector4d initialLinearVelocity  = Tp2Constants::INITIAL_LINEAR_VELOCITY;
        Vector4d initialAngularVelocity = Tp2Constants::INITIAL_ANGULAR_VELOCITY;

        if ( !Tp2Constants::SKIP_DATA_INPUT )
        {
            BOOL breakLoop = promptData(initialLinearVelocity, initialAngularVelocity);
            if ( breakLoop )
                return 0;
        }
        
        cout << endl << "Fermer la fenetre pour recommencer pour revenir a la console" << endl << endl;

        ApplicationManager::get()->startApplication(new Tp2Simulation(&commandLine, 
                                                                      initialLinearVelocity, 
                                                                      initialAngularVelocity));

        // Les resultat sont afficher dans la simulation directement
        ApplicationManager::destroy();

    } while( continueLoop );

    // Will never get to this point
    return 0;
}

// The return value indicate the main loop to break the loop or not
BOOL promptData(Vector4d& initialLinearVelocity, Vector4d& initialAngularVelocity)
{
    STRING simulationStart;
    
    if (!gFirstRun)
    {
        cout << "Pesez la toucher [Enter] pour continuer la simulation ou q pour quitter : ";
        getline(cin, simulationStart);
    }
    gFirstRun = false;

    UINT quitLetterPosition = simulationStart.find("q");
    if ( quitLetterPosition != string::npos )
        return TRUE;

    promptLinearVelocity(initialLinearVelocity);
    promptAngularVelocity(initialAngularVelocity);

    return FALSE;
}

void promptLinearVelocity(Vector4d& initialLinearVelocity)
{
    BOOL validVelocity = FALSE;
    do
    {
        STRING initialVelocityString;
        cout << "Entrez la vitesse lineaire initiale comme suit Vx, Vy, Vz: ";
        getline(cin, initialVelocityString);

        CHAR* nextToken = NULL;
        INT tokenCount = 0;
        CHAR* token = strtok_s((CHAR*) initialVelocityString.c_str(), ", ", &nextToken);
        while (token != NULL && tokenCount < 3) {
            initialLinearVelocity[tokenCount++] = atof(token);
	        token = strtok_s(NULL, ", ", &nextToken);
        }

        validVelocity = tokenCount == 3;
        if ( !validVelocity )
        {
            cout << "Nombre de composants invalide" << endl;
            cout << "Vitesse lineaire initiale invalide, veuillez recommencer" << endl << endl;
        }

    } while( !validVelocity );
}

void promptAngularVelocity(Vector4d& initialAngularVelocity)
{
    BOOL validVelocity = FALSE;
    do
    {
        STRING initialVelocityString;
        cout << "Entrez la vitesse angulaire initiale comme suit Wx, Wy, Wz: ";
        getline(cin, initialVelocityString);

        CHAR* nextToken = NULL;
        INT tokenCount = 0;
        CHAR* token = strtok_s((CHAR*) initialVelocityString.c_str(), ", ", &nextToken);
        while (token != NULL && tokenCount < 3) {
            initialAngularVelocity[tokenCount++] = atof(token);
	        token = strtok_s(NULL, ", ", &nextToken);
        }

        validVelocity = tokenCount == 3;
        if ( !validVelocity )
        {
            cout << "Nombre de composants invalide" << endl;
            cout << "Vitesse angulaire initiale invalide, veuillez recommencer" << endl << endl;
        }

    } while( !validVelocity );
}

