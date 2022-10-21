//
//  MainTableViewController.m
//  LeanOpenGL
//
//  Created by hansen on 2022/10/20.
//

#import "MainTableViewController.h"
#import "MainViewPresenter.h"

@interface MainTableViewController ()

@property (strong, nonatomic) MainViewPresenter *presenter;
@property (strong, nonatomic) NSArray *items;

@end

@implementation MainTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.presenter = [[MainViewPresenter alloc] init];
    self.items = [self.presenter getItems];
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"ID_CELL"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.items.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID_CELL" forIndexPath:indexPath];
    
    cell.textLabel.text = [self.items objectAtIndex: indexPath.row];
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *name = [self.items objectAtIndex:indexPath.row];
    OpenGLViewController *vc = [self.presenter getViewController:name];
    if (vc != nil) {
        [self.navigationController pushViewController:vc animated:YES];
    }
}

@end
