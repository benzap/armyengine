#include <iostream>
#include <string>
#include "ArmyBattleStateMachine.h"

//functions to perform logging within the ArmyBattleStateMachine
#ifdef LOGGING
void log_checkStates(World& world, std::string msg = "") {
	std::cout << "Log - WorldState - " + msg << std::endl;
	std::cout << "world.viewState: " << static_cast<int>(world.viewState) << std::endl;
	std::cout << "world.turnState: " << static_cast<int>(world.turnState) << std::endl;
	for (auto teamDrone : world.getDroneUnits(EnumTeam::BOTH)) {
		std::cout << "Team[" << teamDrone->getTeamID() << "] - "; 
		std::cout << "(" << teamDrone->getDroneID() << ") ";
		std::cout << "DroneState: " << static_cast<int> (teamDrone->getDroneState());
		std::cout << std::endl;
	}
	std::cout << "--" << std::endl;
	std::cout << "FiringDangerZone State" << std::endl;
	std::cout << "Angle: " << world.firingDangerZone.getFiringAngle() / PI * 180 << std::endl;
	std::cout << "Spread: " << world.firingDangerZone.getFiringSpread() / PI * 180 << std::endl;
} //END checkStates(World& world
#else  //LOGGING
void log_checkStates(World& world, std::string msg = "") {}
#endif //LOGGING

ArmyBattleStateMachine::ArmyBattleStateMachine() :
	world(*World::getInstance()) {

}

int ArmyBattleStateMachine::operator() () {
	if (world.viewState == EnumViewState::WORLD) {
		//This state will initialize the next drone
		if (world.turnState == EnumTurnState::INIT) {
			//get the drone list for the current team
			world.teamDroneList = world.getDroneUnits(world.getPlayerTurn());

			//reset the drones to allow input
			for (auto teamDrone : world.teamDroneList) {
				if (teamDrone->getDroneState() != EnumDroneState::DEAD) {
					teamDrone->setDroneState(EnumDroneState::IDLE_WAITING);
					teamDrone->setIdle();
				}
			}

			if (world.teamDroneList.size() == 0) {
				std::cout << "teamDroneList is zero, assuming pre-initialization";
				std::cout << std::endl;
				return 0;
			}
			log_checkStates(world, "Changing from INIT to ASSIGN");

			//status message
			if (world.getPlayerTurn() == EnumTeam::BLUE) {
				world.statusBar.setplayerNextMove("Team BLUE moving currently highlighted unit");
			}
			else {
				world.statusBar.setplayerNextMove("Team RED moving currently highlighted unit");
			}
			world.statusBar.setmostRecentAction("Click in the desired area to move the drone", EnumColor::INFO);

			world.turnState = EnumTurnState::ASSIGN;
		} //END if (turnState == EnumTurnState::INIT) {
		else if (world.turnState == EnumTurnState::ASSIGN) {
			//Assign the next drone to perform the MOVING state
			auto droneIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(), 
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::IDLE_WAITING) {
						return true;
					}
					return false;
			});
			if (droneIter != world.teamDroneList.end()) {
				auto drone = *droneIter;
				drone->setDroneState(EnumDroneState::MOVING);
				drone->setMoving();
				log_checkStates(world, "Changing from ASSIGN to MOVING");
				world.turnState = EnumTurnState::MOVING;

				//status message
				if (world.getPlayerTurn() == EnumTeam::BLUE) {
					world.statusBar.setplayerNextMove("Team BLUE moving currently highlighted unit");
				}
				else {
					world.statusBar.setplayerNextMove("Team RED moving currently highlighted unit");
				}
				world.statusBar.setmostRecentAction("Click in the desired area to move the drone", EnumColor::INFO);
			}
			else {
				//all of the units are gone, thus we switch teams and initialize
				world.changePlayerTurn();
				return 0;
			}


		} //END else if (world.turnState == EnumTurnState::ASSIGN) {
		else if (world.turnState == EnumTurnState::MOVING) {
			//get the currently running drone and ensure it is still within the
			// desired state of MOVING
			auto movingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::MOVING) {
						return true;
					}
					return false;
			});
			//Perform actions on the moving drone
			if (movingIter != world.teamDroneList.end()) {
				auto movingDrone = *movingIter;


				return 0;
			} //END (movingIter != world.teamDroneList.end()) {

			//we don't have a moving drone, so check to see if their is an attacking drone
			// and change the state accordingly
			auto attackingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::ATTACKING) {
						return true;
					}
					return false;
			});
			if (attackingIter != world.teamDroneList.end()) {
				//change our turn state to attacking state, and perform any
				// transition effects
				auto attackingDrone = *attackingIter;
				world.setCurrentDroneID(attackingDrone->getDroneID());
				attackingDrone->setFiring();

				//display our firing danger zone and assign the new position
				// based on the attacking drone's position
				auto position = attackingDrone->getPosition();
				/*world.firingDangerZone.setPosition(
					position[0] + DEFAULT_UNIT_WIDTH/2, 
					position[1] + DEFAULT_UNIT_HEIGHT/2);*/
				world.firingDangerZone.setPosition(
					position[0], 
					position[1]);
				world.firingDangerZone.display();
				log_checkStates(world, "Changing from MOVING to ATTACKING");

				if (world.getPlayerTurn() == EnumTeam::RED) {
					world.statusBar.setplayerNextMove("Team RED attacking with currently highlighted unit");
				}
				else {
					world.statusBar.setplayerNextMove("Team BLUE attacking with currently highlighted unit");
				}
				world.statusBar.setmostRecentAction("Fire: LMB - Spread: UP / DOWN - Skip:  SPACE", EnumColor::INFO);

				world.turnState = EnumTurnState::ATTACKING;
			} //END (attackingIter != world.teamDroneList.end()) {
			else {
				//This shouldn't happen
				std::cout << "ERROR: Incorrect State change between MOVING and ATTACKING";
				std::cout << std::endl;
				return 1;
			}
		} //END else if (world.turnState == EnumTurnState::MOVING) {
		else if (world.turnState == EnumTurnState::ATTACKING) {
			auto attackingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::ATTACKING) {
						return true;
					}
					return false;
			});
			if (attackingIter != world.teamDroneList.end()) {
				//perform actions on the attacking drone
				auto attackingDrone = *attackingIter;
				//the firing action is cleared after it has passed through the system
				if (world.firingDangerZone.hasFired()) {
					world.firingDangerZone.clearFired();
					world.firingDangerZone.hide();
					log_checkStates(world, "Changing from ATTACKING to SENSING");
					attackingDrone->setDroneState(EnumDroneState::SENSING);
				}

				return 0;
			} //END (attackingIter != world.teamDroneList.end()) {

			//we don't have an attacking drone, so check to see if their is an sensing drone
			// and change the state accordingly
			auto sensingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::SENSING) {
						return true;
					}
					return false;
			});
			if (sensingIter != world.teamDroneList.end()) {
				//change our turn state to sensing state, and perform any
				// transition effects
				world.turnState = EnumTurnState::SENSING;
				auto sensingDrone = *sensingIter;
				sensingDrone->setSensing();
				sensingDrone->senseSurroundingUnits();
				sensingDrone->setSensingArea();


				if (world.getPlayerTurn() == EnumTeam::RED) {
					world.statusBar.setplayerNextMove("Team RED sensing... Press ENTER to continue");
				}
				else {
					world.statusBar.setplayerNextMove("Team BLUE sensing... Press ENTER to continue");
				}

				return 0;
			} //END (sensingIter != world.teamDroneList.end()) {
			else {
				//This shouldn't happen
				std::cout << "ERROR: Incorrect State change between ATTACKING and SENSING";
				std::cout << std::endl;
				return 1;
			}
		} //END else if (turnState == EnumTurnState::ATTACKING) {
		else if (world.turnState == EnumTurnState::SENSING) {
			auto sensingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::SENSING) {
						return true;
					}
					return false;
			});
			if (sensingIter != world.teamDroneList.end()) {
				//perform actions on SENSING drone
				auto sensingDrone = *sensingIter;

				return 0;
			} //END (sensingIter != world.teamDroneList.end()) {

			//we don't have aa sensing drone, so check to see if their is a broadcasting drone
			// and change the turn state accordingly
			auto broadcastIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::BROADCASTING) {
						return true;
					}
					return false;
			});
			if (broadcastIter != world.teamDroneList.end()) {
				//change our turn state to broadcasting state, and perform any
				// transition effects
				auto broadcastDrone = *broadcastIter;

				log_checkStates(world, "Changing from SENSING to BROADCASTING");
				world.turnState = EnumTurnState::BROADCASTING;
				broadcastDrone->setBroadcasting();
				broadcastDrone->broadcastCommunication();
				if (world.getPlayerTurn() == EnumTeam::RED) {
					world.statusBar.setplayerNextMove("Team RED broadcasting... Press ENTER to continue");
				}
				else {
					world.statusBar.setplayerNextMove("Team BLUE broadcasting... Press ENTER to continue");
				}
				auto msg = std::string();
				msg += "Drone ";
				msg += std::to_string(broadcastDrone->getDroneID());
				msg += " currently sensing";
				world.statusBar.setmostRecentAction(msg, EnumColor::WARNING);

				return 0;
			} //END (broadcastIter != world.teamDroneList.end()) {
			else {
				//This shouldn't happen
				std::cout << "ERROR: Incorrect State change between SENSING and BROADCASTING";
				std::cout << std::endl;
				return 1;
			}
		} //END else if (world.turnState == EnumTurnState::SENSING) {
		else if (world.turnState == EnumTurnState::BROADCASTING) {
			auto broadcastIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::BROADCASTING) {
						return true;
					}
					return false;
			});
			if (broadcastIter != world.teamDroneList.end()) {
				//perform actions on the BROADCASTING drone
				auto broadcastDrone = *broadcastIter;
				return 0;
			} //END (broadcastIter != world.teamDroneList.end()) {

			//we don't have a broadcasting drone, this is a unique case
			//check to see if their are still waiting drones
			auto waitingIter = std::find_if(world.teamDroneList.begin(), world.teamDroneList.end(),
				[] (std::shared_ptr<DroneUnit> elem) {
					if (elem->getDroneState() == EnumDroneState::IDLE_WAITING) {
						return true;
					}
					return false;
			});
			//check to see if they exist
			if (waitingIter != world.teamDroneList.end()) {
				//we still have waiting drones, so we transition to
				// our assignment state
				log_checkStates(world, "Changing from BROADCASTING to ASSIGN");
				world.turnState = EnumTurnState::ASSIGN;

				return 0;
			}
			else {
				//no waiting drones exist, which means we need 
				// to change the team and reinitialize
				world.changePlayerTurn();
				log_checkStates(world, "Changing from BROADCASTING to INIT");
				world.turnState = EnumTurnState::INIT;
				return 0;
			}
		} //END else if (world.turnState == EnumTurnState::BROADCASTING) {
	} //END if (viewState == EnumViewState::WORLD) {
	else if (world.viewState == EnumViewState::MENU) {
		world.mouseCursor.setIdle();
	} //END else if (viewState == EnumViewState::MENU) {
	else if (world.viewState == EnumViewState::VICTORY) {
		world.mouseCursor.setIdle();
	}

	return 0;
} //END int ArmyBattleStateMachine::operator() () {