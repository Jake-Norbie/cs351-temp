package hw1;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.Test;
import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;

public class TestCreatureTest {
	Thing t = new Thing("Table");
	Tiger c = new Tiger("Gary");
	Ant a = new Ant("Ainsley");
	Bat b = new Bat("Chemsa");
	Fly f = new Fly("Flem");
	Fly h = new Fly("Hugh");
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	
	@Test
	public void test_names() {
		assertEquals(t.toString(), "Table");
		assertEquals(c.toString(), "Gary Tiger");
		assertEquals(a.toString(), "Ainsley Ant");
		assertEquals(b.toString(), "Chemsa Bat");
		assertEquals(f.toString(), "Flem Fly");
	}
	
	@Test
	public void test_nothing_to_eat() {
		System.setOut(new PrintStream(outContent));
		String expected = "Gary Tiger has had nothing to eat!\n";
		c.whatDidYouEat();
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_ant_moves() {
		System.setOut(new PrintStream(outContent));
		String expected = "Ainsley Ant is crawling around.\n";
		a.move();
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_tiger_moves() {
		System.setOut(new PrintStream(outContent));
		String expected = "Gary Tiger has just pounced.\n";
		c.move();
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_bat_moves() {
		System.setOut(new PrintStream(outContent));
		String expected = "Chemsa Bat is swooping through the dark.\n";
		b.move();
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_fly_moves() {
		System.setOut(new PrintStream(outContent));
		String expected = "Flem Fly is buzzing around in flight.\n";
		f.move();
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_eating_things() {
		System.setOut(new PrintStream(outContent));
		String expected = "Table has been eaten by Gary Tiger\nTable has been eaten by Ainsley Ant"
				+ "\nTable has been eaten by Chemsa Bat\nTable has been eaten by Flem Fly\n";
		c.eat(t);
		a.eat(t);
		b.eat(t);
		f.eat(t);
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_eating_creatures() {
		System.setOut(new PrintStream(outContent));
		String expected = "Hugh Fly has been eaten by Gary Tiger\nHugh Fly has been eaten by Ainsley Ant"
				+ "\nChemsa Bat wont eat a Hugh Fly\nFlem Fly wont eat a Hugh Fly\n";
		c.eat(h);
		a.eat(h);
		b.eat(h);
		f.eat(h);
		assertEquals(expected, outContent.toString());
	}
	
	@Test
	public void test_final_meal() {
		c.eat(t);
		a.eat(t);
		b.eat(t);
		f.eat(t);
		c.eat(h);
		a.eat(h);
		b.eat(h);
		f.eat(h);
		System.setOut(new PrintStream(outContent));
		String expected = "Gary Tiger has eaten a Hugh Fly!\nAinsley Ant has eaten a Hugh Fly!"
				+ "\nChemsa Bat has eaten a Table!\nFlem Fly has eaten a Table!\n";
		c.whatDidYouEat();
		a.whatDidYouEat();
		b.whatDidYouEat();
		f.whatDidYouEat();
		assertEquals(expected, outContent.toString());
	}
	
}