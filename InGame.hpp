#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Particles/ParticleSystem.hpp>
#include <Thor/Particles/EmissionInterface.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Math/Random.hpp>
#include <Thor/Time/CallbackTimer.hpp>
#include <array>
#include <memory>
#include <vector>
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Direction.hpp"

// Various constants as firework parameters
const sf::Time	explosionInterval	= sf::seconds(1.f);
const sf::Time	explosionDuration	= sf::seconds(0.2f);
const sf::Time	tailDuration		= sf::seconds(2.5f);
const sf::Int64	tailsPerExplosion	= 15;
const float		gravity				= 30.f;

// Array with possible colors for explosions
const std::array<sf::Color, 9> fireworkColors =
{
	sf::Color(100, 255, 135),	// light green
	sf::Color(175, 255, 135),	// lime green
	sf::Color(85, 190, 255),	// light blue
	sf::Color(255, 145, 255),	// pink
	sf::Color(100, 100, 255),	// indigo
	sf::Color(140, 250, 190),	// turquoise
	sf::Color(255, 135, 135),	// red
	sf::Color(240, 255, 135),	// light yellow
	sf::Color(245, 215, 80),	// light orange
};

// Custom emitter that groups particles in tails
class FireworkEmitter
{
	public:
		explicit FireworkEmitter(sf::Vector2f position)
		: mAccumulatedTime(sf::Time::Zero)
		, mPosition(position)
		, mColor(fireworkColors[thor::random(0u, fireworkColors.size() - 1u)])
		{
		}

		void operator() (thor::EmissionInterface& system, sf::Time dt)
		{
			const sf::Time tailInterval = explosionDuration / tailsPerExplosion;

			// Accumulate passed time. If enough time has passed (tailInterval), emit a new tail and decrease accumulator.
			mAccumulatedTime += dt;
			while (mAccumulatedTime - tailInterval > sf::Time::Zero)
			{
				emitTail(system);
				mAccumulatedTime -= tailInterval;
			}
		}

	private:
		void emitTail(thor::EmissionInterface& system)
		{
			// Create initial direction with random vector length and angle
			thor::PolarVector2f velocity(thor::random(30.f, 70.f), thor::random(0.f, 360.f));

			// Create particle at position of explosion, with emitter-specific color and at 80% initial scale
			thor::Particle particle(tailDuration);
			particle.position = mPosition;
			particle.color = mColor;
			particle.scale *= 0.8f;

			// A tail contains 25 particles with different speeds and scales.
			// The largest particles move fastest, leading to a comet-like tail effect.
			for (sf::Int64 i = 0; i < 25; ++i)
			{
				// Decrease scale continuously
				particle.scale *= 0.95f;

				// Decrease speed continuously
				velocity.r *= 0.96f;
				particle.velocity = velocity;

				// Add adapted particle to particle system
				system.emitParticle(particle);
			}
		}

	private:
		sf::Time		mAccumulatedTime;
		sf::Vector2f	mPosition;
		sf::Color		mColor;
};

// Custom affector that fades particles out and accelerates them according to scale
class FireworkAffector
{
	public:
		void operator() (thor::Particle& particle, sf::Time dt) 
		{
			// Apply gravity, where particles with greater scale are affected stronger (quadratic influence)
			particle.velocity += dt.asSeconds() * sf::Vector2f(0.f, gravity) * particle.scale.x * particle.scale.y;

			// Let particles continuously fade out (particles with smaller scale have already lower alpha value at beginning)
			particle.color.a = static_cast<sf::Uint8>(256 * thor::getRemainingRatio(particle) * particle.scale.x);
		}
};

class InGame {
	public:
		InGame(std::shared_ptr<sf::RenderWindow> window);
		
		bool go();
	
	private:
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<Snake> snake;
		std::shared_ptr<Fruit> fruit;
		Direction direction;
		sf::Clock clock;
		
		sf::Font font;
		sf::Text scoreTxt, speedTxt, pauseTxt;
		
		sf::Music mainMusic;
		sf::SoundBuffer eatFruitBuffer;
		sf::Sound eatFruitSound;
		
		// Tells if we need to respawn a fruit
		bool mustSpawnFruit = true;
		
		// Coords of the fruit
		int fruitX;
		int fruitY;
		
		bool isPaused = false;
		bool isLost = false;
		
		unsigned int score = 0;
		unsigned int speed = 0;
		
		// Instantiate particle system and add custom affector
		thor::ParticleSystem system;
	
		// Create timer that can be connected to callbacks. Initial time limit is 1 second, timer immediately starts
		thor::CallbackTimer explosionTimer;
	
		// Main loop
		sf::Clock frameClock;
};
