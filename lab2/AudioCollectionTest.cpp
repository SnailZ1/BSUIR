#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2/Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AudioCollectionTest
{
	TEST_CLASS(AudioCollectionTest)
	{
	public:
		
		TEST_METHOD(AudioFileTest)
		{
			AudioFile song("505", 4.13, 23, 4, 2037);
			song.setTitle("504");
			song.setDuration(3.10);
			song.setDate(21, 9, 2007);
			song.getTitle();
			song.getInfo();
			song.getDuration();
			song.getDate();
			song.play();
			song.stop();
		}
		TEST_METHOD(MusicTest)
		{
			Music song("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			song.getPerfomer();
			song.setPerfomer("fsdfs");
			song.getInfo();
		}
		TEST_METHOD(PerfomerTest)
		{
			Perfomer person("Nastia", 2013);
			person.setName("fsdfs");
			person.setYearsActive(2015);
			person.getName();
			person.getYearsActive();
		}
		TEST_METHOD(UserTest)
		{
			Music song1("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			Music song2("5053", 4.13, 24, 4, 2007, "Monkeys");
			User p;
			p.setName("Mahmed");
			p.getName();
			p.addToLoveMusic(&song1);
			p.addToLoveMusic(&song2);
			Assert::AreEqual<string>("normal", p.rate(6));
			p.removeFromLoveMusic(2);
			p.checkLoveMusic();
			p.findByTitle("505");
			p.findByDate("23.4.2037");
			p.findByPerfomer("Arctic Monkeys");
		}
		TEST_METHOD(ConcertTest)
		{
			Music song1("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			Music song2("5053", 4.13, 24, 4, 2007, "Monkeys");
			Concert c;
			c.addMusic(&song1);
			c.addMusic(&song2);
			c.removeMusic(2);
			c.setConcertTime("4:55");
			c.setLocation("London");
			c.getConcertTime();
			c.getLocation();
			c.getInfo();
		}
		TEST_METHOD(AlbumTest)
		{
			Music song1("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			Music song2("5053", 4.13, 24, 4, 2007, "Monkeys");
			Album a;
			a.addMusic(&song1);
			a.addMusic(&song2);
			a.getInfo();
			a.sizeOfList();
			a.removeMusic(2);
		}
		TEST_METHOD(RadioStationTest)
		{
			Music song1("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			Music song2("5053", 4.13, 24, 4, 2007, "Monkeys");
			RadioStation rs;
			rs.addToQueue(&song1);
			rs.addToQueue(&song2);
			rs.sizeOfQueue();
			rs.getInfo();
		}
		TEST_METHOD(PlayListTest)
		{
			Music song1("505", 4.13, 23, 4, 2037, "Arctic Monkeys");
			Music song2("5053", 4.13, 24, 4, 2007, "Monkeys");
			PlayList pl;
			pl.addMusic(&song1);
			pl.addMusic(&song2);
			pl.sizeOfList();
			pl.getInfo();
			pl.removeMusic(2);
		}
		TEST_METHOD(AudioBookTest)
		{
			AudioBook book("jhdfsj", 3.12, 12, 2, 32, "fdsfd", 32, 2);
			book.getDate();
			book.getDuration();
			book.getInfo();
			book.getPart();
			book.getPerfomer();
			book.getSize();
			book.getTitle();
			book.play();
			book.stop();
			book.playPage(2);
			book.setSize(45);
		}
	};
}
