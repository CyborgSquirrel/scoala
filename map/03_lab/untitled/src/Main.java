import repo.RepoFriendship;
import repo.RepoUser;
import repo.exception.ItemAlreadyExistsException;
import repo.exception.ItemDoesntExistException;
import service.ServiceFriendship;
import service.ServiceUser;
import service.exception.DependencyDetectedException;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // REPO
        RepoUser repoUser = new RepoUser();
        RepoFriendship repoFriendship = new RepoFriendship();

        // SERVICE
        ServiceUser serviceUser = new ServiceUser(repoUser, repoFriendship);
        ServiceFriendship serviceFriendship = new ServiceFriendship(repoUser, repoFriendship);

        Scanner scanner = new Scanner(System.in);
        while (true) {
            // MENU
            String[] actions = {"user add", "user remove", "friendship add", "friendship remove", "community count"};
            System.out.println("Actions: ");
            for (String action : actions) {
                System.out.println("- " + action);
            }
            System.out.print("> ");

            if (!scanner.hasNextLine()) break;
            String action = scanner.nextLine().strip();
            if (action.isEmpty()) continue;

            try {
                /*--*/ if (action.equals("user add")) {
                    System.out.print("id = "); int id = Integer.parseInt(scanner.nextLine());
                    System.out.print("name = "); String name = scanner.nextLine();
                    serviceUser.addUser(id, name);
                } else if (action.equals("user remove")) {
                    System.out.print("id = "); int id = Integer.parseInt(scanner.nextLine());
                    serviceUser.removeUser(id);
                } else if (action.equals("friendship add")) {
                    System.out.print("id1 = "); int id1 = Integer.parseInt(scanner.nextLine());
                    System.out.print("id2 = "); int id2 = Integer.parseInt(scanner.nextLine());
                    serviceFriendship.addFriendship(id1, id2);
                } else if (action.equals("friendship remove")) {
                    System.out.print("id1 = "); int id1 = Integer.parseInt(scanner.nextLine());
                    System.out.print("id2 = "); int id2 = Integer.parseInt(scanner.nextLine());
                    serviceFriendship.removeFriendship(id1, id2);
                } else if (action.equals("community count")) {
                    int count = serviceFriendship.getCommunitiesCount();
                    System.out.println(count);
                }
            } catch (ItemAlreadyExistsException ex) {
                System.err.println("Item already exists!");
            } catch (ItemDoesntExistException ex) {
                System.err.println("Item doesn't exist!");
            } catch (DependencyDetectedException e) {
                System.err.println("Can't delete user, because user still has friendships!");
            }
        }
    }
}
