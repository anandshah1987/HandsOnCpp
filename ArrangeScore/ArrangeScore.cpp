// ArrangeScore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Student score is saved in txt file in specific format like below :-
//22, Data structure, 45
//23, English, 52
//22, English, 51
//23, Data structure, 61
// First column is student id, second is subject name and third one is score
// Read this data and return average mark scored across all subejcts by student with lowest id

#include <iostream>
#pragma warning(disable : 4996)

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

class Score
{
private :

	unsigned int m_id{};
	std::string m_subject{};
	unsigned int m_score{};

public :

	Score(unsigned int id, std::string subject, unsigned int score):
		m_id(id), m_subject(subject), m_score(score)
	{};

	const unsigned int GetId() const
	{
		return m_id;
	}
	const unsigned int GetScore() const
	{
		return m_score;
	}
};

using StudentScores = std::vector<Score>;

unsigned int processData(StudentScores scores)
{
	if (scores.size() == 0)
	{
		return 0;
	}

	std::sort(scores.begin(), scores.end(), [](const auto& score1, const auto& score2) -> bool
		{
			return score1.GetId() < score2.GetId();
		});

	unsigned int average{};
	auto lowestId = scores.at(0).GetId();
	unsigned int subjectCount = 0;
	unsigned int scoreSum = 0;
	for (const auto& score : scores)
	{
		if (lowestId != score.GetId())
		{
			break;
		}
		subjectCount++;
		scoreSum += score.GetScore();
	}

	return scoreSum / subjectCount;
}

int main()
{
	StudentScores scores;
	std::ifstream inFile("input.txt");
	if (inFile.is_open())
	{
		std::string line;
		while (std::getline(inFile, line))
		{
			std::stringstream ss(line);
			std::string idStr{};
			std::string subject{};
			std::string scoreStr{};
			std::getline(ss, idStr, ',');
			std::getline(ss, subject, ',');
			std::getline(ss, scoreStr, ',');
			unsigned int id = std::stoi(idStr);
			unsigned int score = std::stoi(scoreStr);
			scores.emplace_back(id, subject, score);
		}
	}

	auto result = processData(scores);

	std::ofstream ofile;
	ofile.open("output.txt", std::ios::out);
	ofile << result;
	ofile.close();
	inFile.close();
}
