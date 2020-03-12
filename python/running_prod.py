def consecutive_products(nums, k):
    product = 1
    output = []
    prod_new, i = 1, 0
    
    for index in range(len(nums)):
        product *= nums[index]
        if nums[index] == 0:
            i = 0;
            prod_new = 1
        elif i < k: 
            prod_new *= nums[index] 
            i +=1
            
        if index < k: div = 1
        else: div = nums[index-k]
        
        if div == 0: product = prod_new
        else: product /= div
        output.append(product)
    return output

print(consecutive_products([1, 3, 3, 0, 5, 7, 1, -3], 3))
