package hw1;

public class TestCreature {
    public static void main(String[] args) {
        if (args.length > 0) {
            System.out.println("Too many arguments passed!");
            return;
        }

        Creature creature_list[] = new Creature[8];
        creature_list[0] = new Tiger("Bill");
        creature_list[1] = new Fly("Red");
        creature_list[2] = new Bat("Calvin");
        creature_list[3] = new Ant("Nathan");
        creature_list[4] = new Tiger("Thanos");
        creature_list[5] = new Ant("Billiam");
        creature_list[6] = new Fly("Gold");
        creature_list[7] = new Bat("Melstrum");
        
        Thing thing_list[] = new Thing[12];
        thing_list[0] = new Thing("Toaster");
        thing_list[1] = new Thing("Computer");
        thing_list[2] = new Thing("Orange");
        thing_list[3] = new Thing("Robot Leg");
        for (int cnvrt = 4; cnvrt < 12; cnvrt++) {
            thing_list[cnvrt] = creature_list[cnvrt-4];
        }
        
        System.out.println("Things:\n");
        for (int t = 0; t < 12; t++) {
            System.out.println(thing_list[t].toString());
        }
        System.out.println("\nCreatures:\n");
        for (int c = 0; c < 8; c++) {
            System.out.println(thing_list[c+4].toString());
        }

        System.out.println("\nCreatures Saying They Have Had Nothing To Eat: \n");
        for (int c = 0; c < 8; c++) {
            creature_list[c].whatDidYouEat();
        }
        System.out.println("\nCreatures Moving: \n");
        for (int c = 0; c < 8; c++) {
            creature_list[c].move();
        }
        System.out.println("\nCreatures Eating Things: \n");
        for (int c = 0; c < 8; c++) {
            creature_list[c].eat(new Thing("Mysterious Object"));
        }
        System.out.println("\nCreatures Eating Creatures: \n");
        for (int c = 0; c < 8; c++) {
            creature_list[c].eat(new Ant("James"));
        }
        System.out.println("\nThe Last Thing Creatures Ate: \n");
        for (int c = 0; c < 8; c++) {
            creature_list[c].whatDidYouEat();
        }
        System.out.println();
    }
}

class Thing {
    final String name;
    public Thing(String s) {
        name = s;
    }

    public String toString() {
        if (getClass().getSimpleName().equals("Thing")) {
            return name;
        } else {
            return name + " " + getClass().getSimpleName();
        }
    }
}

abstract class Creature extends Thing {
    
    String lastAte;

    public Creature(String s) {
        super(s);
    }

    public void eat(Thing aThing) {
        lastAte = aThing.toString();
        System.out.print(aThing.toString() + " has been eaten by " + this.toString() + "\n");
    }

    public abstract void move();

    public void whatDidYouEat() {
        if (lastAte == null || lastAte.equals("")) {
            System.out.print(this.toString() + " has had nothing to eat!\n");
        } else {
            System.out.print(this.toString() + " has eaten a " + lastAte + "!\n");
        }
    }
}

interface Flyer{
    public abstract void fly();
}

class Tiger extends Creature {
    public Tiger(String s) {
        super(s);
    }
    
    public void move() {
        System.out.print(this.toString() + " has just pounced.\n");
    }
}

class Ant extends Creature {
    public Ant(String s) {
        super(s);
    }
    
    public void move() {
        System.out.print(this.toString() + " is crawling around.\n");
    }
}

class Bat extends Creature implements Flyer {
    public Bat(String s) {
        super(s);
    }

    public void move() {
        fly();
    }
    
    public void fly() {
        System.out.print(this.toString() + " is swooping through the dark.\n");
    }

    public void eat(Thing aThing) {
        if (aThing instanceof Creature) {
            System.out.print(this.toString() + " wont eat a " + aThing.toString() + "\n");
        } else {
            super.eat(aThing);
        }
    }
}

class Fly extends Creature implements Flyer {
    public Fly(String s) {
        super(s);
    }

    public void move() {
        fly();
    }
    
    public void fly() {
        System.out.print(this.toString() + " is buzzing around in flight.\n");
    }

    public void eat(Thing aThing) {
        if (aThing instanceof Creature) {
            System.out.print(this.toString() + " wont eat a " + aThing.toString() + "\n");
        } else {
            super.eat(aThing);
        }
    }
}
