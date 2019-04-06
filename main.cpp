#include <iostream>

/**
 *  El juego consiste en un recipiente con un total de 13 caramelos
 *  y un ají picante, del cual los jugadores podran sacar entre 1 y 3
 *  caramelos por turno. El perdedor será el jugador que solo tenga para
 *  elegir el ají en su turno.
 *  El algoritmo para ganar consiste en sacar un solo caramelo al principio,
 *  y luego en las siguientes rondas sacar la misma cantidad de caramelos que
 *  sacó el otro jugador en la ronda anterior, siempre y cuando sea mayor la
 *  cantidad de caramelos que quedaron en el recipiente que la cantidad que sacó
 *  en el turno anterior ( sería ilógico querer sacar 3 cuando quedan 2 o 1 ).
 *  Por ejemplo:
 *
 *  RONDA JUGADOR I - JUGADOR 2 - TOTAL DE CARAMELOS
 *    1    saca 1      saca 2        13 - 3 = 10
 *    2    saca 2      saca 2        10 - 4 = 6
 *    3    saca 2      saca 3        6 - 5 = 1
 *    4    saca 1      pierde
 */

/*
class Glass {
public:
    Glass( void ) {}

    int getCountOfCandies( void ) ;

private:
    enum { MAX_CANDIES = 13 } ;

    int count = MAX_CANDIES ;

} ;
*/


class Player {
public:
    Player( void ) : lost( false ), turnIdentifier( 0 ) {}
    Player( int turn_id ) : lost( false ), turnIdentifier( turn_id ) {}

    bool hasLost( void ) { return lost ; }
    void changeStateToLost( void ) { lost = true ; }
    int getTurnId( void ) { return turnIdentifier ; }

private:
    bool lost ;
    int turnIdentifier ;

};

int main()
{
    // Primera iteración
    typedef int Candies ;

    Candies candies = 13 ;

    Player playerOne( 1 ), playerTwo( 2 ) ;
    int currentTurn = playerOne.getTurnId() ; // siempre arranca el jugador uno

    std::cout << "*  El juego consiste en un recipiente con un total de 13 caramelos\n"
                 "*  y un ají picante, del cual los jugadores podran sacar entre 1 y 3\n"
                 "*  caramelos por turno. El perdedor será el jugador que solo tenga para\n"
                 "*  elegir el ají en su turno.\n" ;
    std::cout << "-------------------------------------------------------------------------" << std::endl ;
    std::cout << "Total de caramelos: " << candies << std::endl ;


    while ( !playerOne.hasLost() && !playerTwo.hasLost() ) {
        int candiesTaked = 0 ;
        int round = 0 ;

        std::cout << "Ronda " << round << std::endl ;

        if ( playerOne.getTurnId() == currentTurn ) {
            // arranca el turno del jugador uno
            if ( candies > 0 ) {
                std::cout << "Jugador uno saca: " ;
                std::cin >> candiesTaked ; // toma esa cantidad de caramelos
                if ( candiesTaked > candies || candiesTaked > 3 ) { // corrobora que no se intente sacar más de los que hay
                    while ( candiesTaked > candies || candiesTaked > 3 ) {
                        std::cout << "Saque menos: " ;
                        std::cin >> candiesTaked ;
                    }
                }
                candies = candies - candiesTaked ; // se descuenta esa cantidad de caramelos del total
                std::cout << "Total de caramelos: " << candies << std::endl ;
                currentTurn = playerTwo.getTurnId() ; // cede el turno al segundo jugador
            } else {
                playerOne.changeStateToLost(); ;
            }
        } else {
            // arranca el turno del jugador dos
            if ( candies > 0 ) {
                std::cout << "Jugador dos saca: " ;
                std::cin >> candiesTaked ; // toma esa cantidad de caramelos
                if ( candiesTaked > candies || candiesTaked > 3 ) { // corrobora que no se intente sacar más de los que hay
                    while ( candiesTaked > candies || candiesTaked > 3 ) {
                        std::cout << "Saque menos: " ;
                        std::cin >> candiesTaked ;
                    }
                }
                candies = candies - candiesTaked ; // se descuenta esa cantidad de caramelos del total
                std::cout << "Total de caramelos: " << candies << std::endl ;
                currentTurn = playerOne.getTurnId() ; // cede el turno al segundo jugador
            } else {
                playerTwo.changeStateToLost(); ;
            }
        }

        std::cout << std::endl ;
        round++ ; // pasa a la siguiente ronda

    }

    // verifica quien perdió
    if ( playerOne.hasLost() ) {
        std::cout << "Player one lost" << std::endl ;
    } else {
        std::cout << "Player two lost" << std::endl ;
    }

    return 0;
}
