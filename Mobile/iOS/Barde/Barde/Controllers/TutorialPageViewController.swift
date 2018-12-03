
//
//  TutorialPageViewo.swift
//  Barde
//
//  Created by Arnaud Perrault on 23/11/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import Foundation
import UIKit

class TutorialPageViewController: UIPageViewController, AppWalkThroughDelegate
{
    lazy var pages: [UIViewController] = {
        let first = Page1ViewController()
        
        first.delegate = self
        return [
            self.getViewController(withIdentifier: "Page1"),
            self.getViewController(withIdentifier: "TutorialStyleView"),
            self.getViewController(withIdentifier: "TutorialAAView"),
            self.getViewController(withIdentifier: "TutorialBatteryView"),
            self.getViewController(withIdentifier: "TutorialBPMView"),
            
            self.getViewController(withIdentifier: "TutorialListenView"),
            self.getViewController(withIdentifier: "TutorialEndView")
        ]
    }()
    
    fileprivate func getViewController(withIdentifier identifier: String) -> UIViewController
    {
        return UIStoryboard(name: "Tutorial", bundle: nil).instantiateViewController(withIdentifier: identifier)
    }
    
    var pageControl = UIPageControl()
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        self.dataSource = self
        self.delegate   = self
        
        configurePageControl()
        print("ok")
        if let firstVC = pages.first
        {
//            goNextPage(forwardTo: 1)
            setViewControllers([firstVC], direction: .forward, animated: true, completion: nil)
        }
    }
    
    func configurePageControl() {
        
        pageControl = UIPageControl(frame: CGRect(x: 0, y: UIScreen.main.bounds.maxY - 180, width: UIScreen.main.bounds.width, height: 50))
        
        self.pageControl.numberOfPages = pages.count
        self.pageControl.currentPage = 0
        self.pageControl.tintColor = Utils().uicolorFromHex(rgbValue: 0xFFFFFF)
        self.pageControl.pageIndicatorTintColor = Utils().uicolorFromHex(rgbValue: 0xFFFFFF)
        self.pageControl.currentPageIndicatorTintColor = Utils().uicolorFromHex(rgbValue: 0xD53972)
        self.view.addSubview(pageControl)
    }
    
    func goNextPage(forwardTo position: Int) {

        setViewControllers([pages.first!], direction:
            UIPageViewController.NavigationDirection.forward, animated: false, completion: nil)
        
    }
    
}

extension TutorialPageViewController: UIPageViewControllerDataSource
{
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerBefore viewController: UIViewController) -> UIViewController? {
        
        guard let viewControllerIndex = pages.index(of: viewController) else { return nil }
        
        let previousIndex = viewControllerIndex - 1
        
        guard previousIndex >= 0          else { return nil }
        
        guard pages.count > previousIndex else { return nil        }
        
        return pages[previousIndex]
    }
    
    func pageViewController(_ pageViewController: UIPageViewController, viewControllerAfter viewController: UIViewController) -> UIViewController?
    {
        guard let viewControllerIndex = pages.index(of: viewController) else { return nil }
        
        let nextIndex = viewControllerIndex + 1
        
        guard nextIndex < pages.count else { return nil }
        
        guard pages.count > nextIndex else { return nil         }
        
        return pages[nextIndex]
    }
    // MARK: Delegate functions
    func pageViewController(_ pageViewController: UIPageViewController, didFinishAnimating finished: Bool, previousViewControllers: [UIViewController], transitionCompleted completed: Bool) {
        let pageContentViewController = pageViewController.viewControllers![0]
        self.pageControl.currentPage = pages.index(of: pageContentViewController)!
    }
}

extension TutorialPageViewController: UIPageViewControllerDelegate { }

@objc protocol AppWalkThroughDelegate {
    @objc optional func goNextPage(forwardTo position: Int)
}
