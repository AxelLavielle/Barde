//
//  ViewController.swift
//  Barde
//
//  Created by Arnaud Perrault on 10/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

 class ViewController: UIViewController, NSFetchedResultsControllerDelegate{
    
    @IBOutlet weak var contentView: UIView!
    @IBOutlet var menuButtons: [UIButton]!
    
    var profilViewController: UIViewController!
    var mainViewController: UIViewController!
    var settingsViewController: UINavigationController!
    
    var viewControllers: [UIViewController]!
    var selectedIndex: Int = 0
    

    
    @IBAction func didPressTab(_ sender: UIButton) {
        let previousIndex = selectedIndex

        selectedIndex = sender.tag

        menuButtons[previousIndex].isSelected = false
        
        let previousVC = viewControllers[previousIndex]
        previousVC.willMove(toParentViewController: nil)
        previousVC.view.removeFromSuperview()
        previousVC.removeFromParentViewController()
        
        sender.isSelected = true
        let vc = viewControllers[selectedIndex]
        addChildViewController(vc)
        
        vc.view.frame = contentView!.bounds
        //intially set x = SCREEN_WIDTH
        
        UIView.transition(with: self.contentView!, duration: 0.5, options: .transitionFlipFromLeft, animations: { () in
            self.contentView!.addSubview(vc.view)
        }, completion: nil)
        
        //contentView!.addSubview(vc.view)
        vc.didMove(toParentViewController: self)
        
    
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        profilViewController = storyboard.instantiateViewController(withIdentifier: "ProfilViewController")
        mainViewController = storyboard.instantiateViewController(withIdentifier: "MainViewController")
        settingsViewController = storyboard.instantiateViewController(withIdentifier: "SettingsViewController") as! UINavigationController
        
        viewControllers = [profilViewController, mainViewController, settingsViewController]

        menuButtons[selectedIndex].isSelected = true
        didPressTab(menuButtons[selectedIndex])
        
        //// TODO: Remove, only for test
        //test()
        /////
        
       

    }
    
    
    func test() {
        
        let profil = Profil(context: context)
        profil.email = "arnaud.p@outlook.fr"
        profil.firstname = "Arnaud"
        profil.lastname = "Perrault"
    
        ad.saveContext()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
   

}

