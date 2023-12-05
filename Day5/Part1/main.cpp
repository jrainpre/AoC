#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

struct range{
    long dest = 0;
    long source = 0;
    long range = 0;
};

struct recipe{
    long seed = 0;
    long soil = 0;
    long fertilizer = 0;
    long water = 0;
    long light = 0;
    long temperature = 0;
    long humidity = 0;
    long location = 0;
};


enum Mode{
    SEED,
    SEED_SOIL,
    SOIL_FERTILIZER,
    FERTILIZER_WATER,
    WATER_LIGHT, 
    LIGHT_TEMPERATURE,
    TEMPERATURE_HUMIDITY,
    HUMIDITY_LOCATION,
};

bool is_in_range(long value, range r)
{
    if (value >= r.source && value <= r.source + r.range)
        return true;
    return false;
}

    std::vector<recipe> getSoilForSeed(recipe rec, std::vector<range> seed_soil)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.soil = rec.seed;
        for (auto r : seed_soil)
        {
    
            if (is_in_range(rec.seed, r))
            {
                new_rec.soil = rec.seed + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }

        }   
         if (found == false)
            recipes.push_back(new_rec); 
        return recipes;
    }

    std::vector<recipe> getFertilizerForSoil(recipe rec, std::vector<range> soil_fertilizer)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.fertilizer = rec.soil;
        for (auto r : soil_fertilizer)
        {

            if (is_in_range(rec.soil, r))
            {
                new_rec.fertilizer = rec.soil + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }

    std::vector<recipe> getWaterForFertilizer(recipe rec, std::vector<range> fertilizer_water)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.water = rec.fertilizer;
        for (auto r : fertilizer_water)
        {
            recipe new_rec = rec;
            new_rec.water = rec.fertilizer;
            if (is_in_range(rec.fertilizer, r))
            {
                new_rec.water = rec.fertilizer + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }

    std::vector<recipe> getLightForWater(recipe rec, std::vector<range> water_light)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.light = rec.water;
        for (auto r : water_light)
        {
            recipe new_rec = rec;
            new_rec.light = rec.water;
            if (is_in_range(rec.water, r))
            {
                new_rec.light = rec.water + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }

    std::vector<recipe> getTemperatureForLight(recipe rec, std::vector<range> light_temperature)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.temperature = rec.light;
        for (auto r : light_temperature)
        {
            recipe new_rec = rec;
            new_rec.temperature = rec.light;
            if (is_in_range(rec.light, r))
            {
                new_rec.temperature = rec.light + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }



    std::vector<recipe> getHumidityForTemperature(recipe rec, std::vector<range> temperature_humidity)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.humidity = rec.temperature;
        for (auto r : temperature_humidity)
        {
            recipe new_rec = rec;
            new_rec.humidity = rec.temperature;
            if (is_in_range(rec.temperature, r))
            {
                new_rec.humidity = rec.temperature + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }


    std::vector<recipe> getLocationForHumidity(recipe rec, std::vector<range> humidity_location)
    {
        std::vector<recipe> recipes;
        bool found = false;
        recipe new_rec = rec;
        new_rec.location = rec.humidity;
        for (auto r : humidity_location)
        {
            recipe new_rec = rec;
            new_rec.location = rec.humidity;
            if (is_in_range(rec.humidity, r))
            {
                new_rec.location = rec.humidity + r.dest - r.source;
                recipes.push_back(new_rec);
                found = true;
            }
        }
        if (found == false)
            recipes.push_back(new_rec);
        return recipes;
    }


long get_smallest(std::vector<long> input)
{
    long smallest = input[0];
    for (auto i : input)
    {
        if (i < smallest)
            smallest = i;
    }
    return smallest;
}

int main(int argc, char **argv)
{
    std::vector<long> seeds;
    std::vector<long> soils;
    std::vector<long> fertilizers;
    std::vector<long> waters;
    std::vector<long> lights;
    std::vector<long> temperatures;
    std::vector<long> humidities;
    std::vector<long> locations;

    std::vector<recipe> recipes;

    std::vector<range> seed_soil;
    std::vector<range> soil_fertilizer;
    std::vector<range> fertilizer_water;
    std::vector<range> water_light;
    std::vector<range> light_temperature;
    std::vector<range> temperature_humidity;
    std::vector<range> humidity_location;



    std::ifstream file("input.txt");
    if (!file.is_open())
        {   
        std::cerr << "Problem with open input file" << std::endl;
        exit(1);
        }
    std::string line;
    long count = 0;
    bool to_skip = false;
    long number = 0;
    long mode = Mode::SEED;
    count = 0;
    while (getline(file, line))
    {
        if (line.empty())
        {
            mode++;
            to_skip = true;
            continue;
        }
        switch (mode)
        {
        case Mode::SEED:
        {
            long rangeSeed[2];
          std::string testest = line.substr(line.find_first_of(':') + 1);
             std::istringstream seedsstr(testest);
            while (seedsstr >> number ) {
                if (count < 2)
                {
                    rangeSeed[count] = number;
                    count++;
                }
                if (count == 2)
                {
                    for (long i = rangeSeed[0]; i <= rangeSeed[1] + rangeSeed[0]; i++)
                    {
                        //std::cout << seeds.size() << std::endl;
                        seeds.push_back(i);
                    }
                    count = 0;
                }
         }
    }
            break;
        case Mode::SEED_SOIL:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            seed_soil.push_back(r);
        }
            break;
        case Mode::SOIL_FERTILIZER:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            soil_fertilizer.push_back(r);
        }
            break;
        case Mode::FERTILIZER_WATER:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            fertilizer_water.push_back(r);
        }
            break;
        case Mode::WATER_LIGHT:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            water_light.push_back(r);
        }
            break;
        case Mode::LIGHT_TEMPERATURE:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            light_temperature.push_back(r);
        }
            break;
        case Mode::TEMPERATURE_HUMIDITY:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            temperature_humidity.push_back(r);
        }
            break;
        case Mode::HUMIDITY_LOCATION:
        {
            if (to_skip)
            {
                to_skip = false;
                continue;
            }
            range r;
            std::istringstream seedstr(line);
            seedstr >> r.dest >> r.source >> r.range;
            humidity_location.push_back(r);
        }
            break;
        default:
            break;
        }
        }


        std::vector<recipe> soil_recipes;
        std::vector<recipe> fertilizer_recipes;
        std::vector<recipe> water_recipes;
        std::vector<recipe> light_recipes;
        std::vector<recipe> temperature_recipes;
        std::vector<recipe> humidity_recipes;
        std::vector<recipe> location_recipes;
        std::vector<recipe> temp;
      
            recipe rec;

            for (auto seed: seeds)
            {
                rec.seed = seed;
                temp = getSoilForSeed(rec, seed_soil);
                soil_recipes.insert(soil_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }
            for (auto soil_rec : soil_recipes)
            {
                temp = getFertilizerForSoil(soil_rec, soil_fertilizer);
                fertilizer_recipes.insert(fertilizer_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }
            for (auto fertilizer_rec : fertilizer_recipes)
            {
                temp = getWaterForFertilizer(fertilizer_rec, fertilizer_water);
                water_recipes.insert(water_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }

            for (auto water_rec : water_recipes)
            {
                temp = getLightForWater(water_rec, water_light);
                light_recipes.insert(light_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }

            for (auto light_rec : light_recipes)
            {
                temp = getTemperatureForLight(light_rec, light_temperature);
                temperature_recipes.insert(temperature_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }

            for (auto temperature_rec : temperature_recipes)
            {
                temp = getHumidityForTemperature(temperature_rec, temperature_humidity);
                humidity_recipes.insert(humidity_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }

            for (auto humidity_rec : humidity_recipes)
            {
                temp = getLocationForHumidity(humidity_rec, humidity_location);
                location_recipes.insert(location_recipes.end(), temp.begin(), temp.end());
                temp.clear();
            }

            long smallest_location = location_recipes[0].location;
            for (auto rec : location_recipes)
            {
                if (rec.location < smallest_location)
                    smallest_location = rec.location;
            }        

long test = 0;
std::cout << "Smallest location: " << smallest_location << std::endl;
    return 0;

        
}
